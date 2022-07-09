#include"chef.hpp"

using namespace std;

Chef::~Chef() {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        delete recipes[i];
}
Chef::Chef(string username_, string password_, string type_)
    : Person(username_, password_, type_) {
    rating = 0;
}
Recipe* Chef::add_recipe(string title_, string vegeterian_, string image_addres_,
    string minutes, string tags_, string ingredients_, int id) {
    vector<string> ingredients, tags;
    int  minutes_to_ready;
    string  title, image_addres, vegeterian;
    title = title_;
    ingredients = separating_words(ingredients_, ',');
    vegeterian = vegeterian_;
    minutes_to_ready = stoi(minutes);
    tags = separating_words(tags_, ',');
    image_addres = image_addres_;
    Recipe* recipe = new Recipe(ingredients, tags, id, minutes_to_ready,
        this->get_username(), title, image_addres, vegeterian);
    recipes.push_back(recipe);
    return recipe;
}
double Chef::calculate_rating() {
    double sum = 0, counter = 0;
    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        if (recipes[i]->is_rated()) {
            sum += recipes[i]->get_rating();
            counter++;
        }
    }
    if (counter == 0)
        return 0;
    return sum / counter;
}
double Chef::get_rating() {
    rating = ceil(calculate_rating() * 10) / 10;
    return rating;
}
int Chef::find_recipe(int id) {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        if (id == recipes[i]->get_id())
            return i;
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void Chef::delete_from_recipes(int id, vector<Recipe*>& all_recipes, vector<Recipe*>& deleted_recipes) {
    int index;
    for (index = 0; index < static_cast<int>(all_recipes.size()); index++)
        if (id == all_recipes[index]->get_id())
            break;
    deleted_recipes.push_back(all_recipes[index]);
    all_recipes.erase(all_recipes.begin() + index);
}
void Chef::delete_recipe(int id, vector<Recipe*>& all_recipes, vector<Recipe*>& deleted_recipes) {
    Recipe* want_delete = recipes[find_recipe(id)];
    delete_from_recipes(id, all_recipes, deleted_recipes);
    recipes.erase(recipes.begin() + find_recipe(id));
}
vector<Recipe*> Chef::get_my_recipes() {

    return recipes;
}
void Chef::add_new_shelf(string name, int id) {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
Shelf* Chef::get_new_shelf() {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
vector<Shelf*> Chef::get_shelves() {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void Chef::add_recipe_to_shelf(int shelf_id, Recipe* recipe) {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void Chef::delete_recipe_from_shelf(int shelf_id, int recipe_id) {
    throw runtime_error(PERMISSION_DENIED_TXT);
}