#include"shelf.hpp"

using namespace std;

Shelf::Shelf(string name_, string user_username_, int id_) {
    name = name_;
    user_username = user_username_;
    id = id_;
}
bool Shelf::is_new_recipe(Recipe* recipe) {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        if (recipes[i]->get_id() == recipe->get_id())
            return false;
    return true;
}
bool Shelf::contain_recipe(int id) {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        if (recipes[i]->get_id() == id)
            return true;
    return false;
}
int Shelf::find_recipe(int recipe_id) {
    for (int i = 0; i < static_cast<int>(recipes.size()); i++)
        if (recipes[i]->get_id() == recipe_id)
            return i;
    throw runtime_error(BAD_REQUEST_TXT);
}
void Shelf::delete_recipe(int recipe_id) {
    int index = find_recipe(recipe_id);
    recipes.erase(recipes.begin() + index);
}
void Shelf::add_recipe(Recipe* recipe) {
    if (is_new_recipe(recipe))
        recipes.push_back(recipe);
    else
        throw runtime_error(BAD_REQUEST_TXT);
}
string Shelf::get_info() {
    ostringstream info;
    info << id << " " << name;
    return info.str();
}
int Shelf::get_id() { return id; }
string Shelf::get_name() { return name; }
vector<Recipe*> Shelf::get_recipes() { return recipes; }