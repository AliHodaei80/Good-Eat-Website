#include"user.hpp"

using namespace std;

User::User(string username_, string password_, string type_)
    : Person(username_, password_, type_) {

}
Shelf* User::find_shelf(int id) {
    for (int i = 0; i < static_cast<int>(my_shelves.size()); i++)
        if (id == my_shelves[i]->get_id())
            return my_shelves[i];
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void User::add_recipe_to_shelf(int shelf_id, Recipe* recipe) {
    Shelf* shelf = find_shelf(shelf_id);
    shelf->add_recipe(recipe);
}
Recipe* User::add_recipe(string title_, string vegeterian_, string image_addres_,
    string minutes, string tags_, string ingredients_, int id) {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void User::add_new_shelf(string name, int id) {
    Shelf* new_shelf = new Shelf(name, username, id);
    my_shelves.push_back(new_shelf);
}
Shelf* User::get_new_shelf() { return my_shelves[my_shelves.size() - 1]; }
vector<Shelf*> User::get_shelves() {
    return my_shelves;
}
void User::delete_recipe_from_shelf(int shelf_id, int recipe_id) {
    Shelf* shelf = find_shelf(shelf_id);
    shelf->delete_recipe(recipe_id);
}
double User::get_rating() {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
void User::delete_recipe(int id, vector<Recipe*>& all_recipes, vector<Recipe*>& deleted_recipes) {
    throw runtime_error(PERMISSION_DENIED_TXT);
}
vector<Recipe*> User::get_my_recipes() {
    throw runtime_error(PERMISSION_DENIED_TXT);
}