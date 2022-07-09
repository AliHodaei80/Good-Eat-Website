#include"good_eat.hpp"

using namespace std;

Good_Eats::Good_Eats() {
    deleted_recipe_num = 0;
}
Good_Eats::~Good_Eats() {
    for (int index = 0; index < static_cast<int>(people.size()); index++)
        delete people[index];
    for (int i = 0; i < static_cast<int>(shelves.size()); i++)
        delete shelves[i];
    for (int index = 0; index < static_cast<int>(deleted_recipes.size()); index++)
        delete deleted_recipes[index];
}
void Good_Eats::add_recipe_to_shelf(string username, string shelf_id_, string recipe_id_) {
    int shelf_id = stoi(shelf_id_), recipe_id = stoi(recipe_id_);
    find_person(username)->add_recipe_to_shelf(shelf_id, find_recipe(recipe_id));
}
string Good_Eats::get_all_upeople() {
    vector<Person*> sorted_people = sorting.sorting_people(people);
    ostringstream body;
    bool is_empty = true;
    for (int i = 0; i < static_cast<int>(sorted_people.size()); i++) {
        body << sorted_people[i]->get_username() << endl;
        is_empty = false;
    }
    if (is_empty)
        body << EMPTY_TXT << endl;
    return body.str();

}
vector<Recipe*> Good_Eats::get_recipes() { return recipes; }

Recipe* Good_Eats::find_recipe(int id) {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        if (recipes[i]->get_id() == id)
            return recipes[i];
    }
    for (int i = 0; i < static_cast<int>(deleted_recipes.size()); i++) {
        if (deleted_recipes[i]->get_id() == id)
            return deleted_recipes[i];
    }
    throw runtime_error(NOT_FOUND_TXT);
}
vector<Shelf*> Good_Eats::get_user_shelves(string username) {
    Person* person = find_person(username);
    return person->get_shelves();
}
Shelf* Good_Eats::find_shelf(int id) {
    for (int i = 0; i < static_cast<int>(shelves.size()); i++)
        if (shelves[i]->get_id() == id)
            return shelves[i];
    throw runtime_error(NOT_FOUND_TXT);
}
void Good_Eats::delete_shelves_recipes(string username, string shelf_id_, string recipe_id_) {
    int shelf_id = stoi(shelf_id_);
    int recipe_id = stoi(recipe_id_);
    Shelf* check_existence = find_shelf(shelf_id);
    find_person(username)->delete_recipe_from_shelf(shelf_id, recipe_id);
}
void Good_Eats::delete_recipe(string username, string recipe_id) {
    int id = stoi(recipe_id);
    find_person(username)->delete_recipe(id, recipes, deleted_recipes);
    deleted_recipe_num++;
}
void Good_Eats::add_recipe(string name, string title_, string vegeterian_, string image_addres_,
    string minutes, string tags_, string ingredients_) {
    Recipe* new_recipe = nullptr;
    try {
        new_recipe = find_person(name)->add_recipe(title_, vegeterian_, image_addres_,
            minutes, tags_, ingredients_, recipes.size() + deleted_recipe_num + 1);
        recipes.push_back(new_recipe);
    }
    catch (...) {
        delete new_recipe;
        throw;
    }
}
void Good_Eats::rate_recipe(string username, string id_, string score_, string rated_before) {
    int id = 0, score = 0;
    id = stoi(id_);
    score = stoi(score_);
    Recipe* recipe = find_recipe(id);
    if (rated_before == "no")
        recipe->is_rating(score, find_person(username)->get_username());
    else if (rated_before == "yes")
        recipe->is_re_rating(score, find_person(username)->get_username());
}
void Good_Eats::add_shelf(string username, string shelf_name) {
    find_person(username)->add_new_shelf(shelf_name, shelves.size() + 1);
    shelves.push_back(find_person(username)->get_new_shelf());
}
Person* Good_Eats::find_person(string username) {
    for (int i = 0; i < static_cast<int>(people.size()); i++)
        if (username == people[i]->get_username())
            return people[i];
    return nullptr;
}
void Good_Eats::login(string username, string password) {
    Person* want_login = find_person(username);
    if (want_login == nullptr)
        throw runtime_error("You haven't signed up.");
    if (password != want_login->get_password())
        throw runtime_error("Password doesn't matched.");
}
void Good_Eats::signup(string username, string password, string type) {
    if (find_person(username) != nullptr)
        throw runtime_error("You have signed up before.");
    if (type == USER) {
        User* user = new User(username, password, type);
        people.push_back(user);
    }
    else if (type == CHEF) {
        Chef* chef = new Chef(username, password, type);
        people.push_back(chef);
    }
    else
        throw runtime_error(BAD_REQUEST_TXT);
}
vector<Recipe*> Good_Eats::get_not_added_recipes_from(Shelf* shelf) {
    vector<Recipe*> not_added_recipes;
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        if (!shelf->contain_recipe(recipes[i]->get_id()))
            not_added_recipes.push_back(recipes[i]);
    return not_added_recipes;
}
int Good_Eats::get_recipes_num() { return recipes.size(); }