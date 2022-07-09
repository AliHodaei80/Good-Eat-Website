#ifndef SHELF_H
#define SHELF_H

#include<iostream>
#include<vector>
#include<fstream>
#include <sstream>
#include"recipe.hpp"
#include"sorting.hpp"

class Shelf {
private:
    int id;
    std::string name;
    std::string user_username;
    std::vector<Recipe*> recipes;
    Sorting_Objects sorting;
public:
    Shelf(std::string name_, std::string user_username_, int id_);
    bool is_new_recipe(Recipe* recipe);
    bool contain_recipe(int id);
    int find_recipe(int recipe_id);
    void delete_recipe(int recipe_id);
    void add_recipe(Recipe* recipe);
    std::vector<Recipe*> get_recipes();
    std::string get_info();
    int get_id();
    std::string get_name();
};
#endif
