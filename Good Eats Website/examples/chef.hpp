#ifndef CHEF_H
#define CHEF_H

#include<iostream>
#include<vector>
#include"recipe.hpp"
#include"person.hpp"
#include"sorting.hpp"
#include"shelf.hpp"
#include"inputs.hpp"

class Chef :public Person {
private:
    double rating;
    std::vector<Recipe*> recipes;
    Sorting_Objects sorting;
public:
    Chef(std::string username_, std::string password_, std::string type_);
    ~Chef();
    virtual Recipe* add_recipe(std::string title_, std::string vegeterian_, std::string image_addres_,
        std::string minutes, std::string tags_, std::string ingredients_, int id);
    double calculate_rating();
    double get_rating();
    int find_recipe(int id);
    void delete_from_recipes(int id, std::vector<Recipe*>& all_recipes, std::vector<Recipe*>& deleted_recipes);
    void delete_recipe(int id, std::vector<Recipe*>& all_recipes, std::vector<Recipe*>& deleted_recipes);
    std::vector<Recipe*> get_my_recipes();
    virtual void add_new_shelf(std::string name, int id);
    virtual Shelf* get_new_shelf();
    std::vector<Shelf*> get_shelves();
    void add_recipe_to_shelf(int shelf_id, Recipe* recipe);
    void delete_recipe_from_shelf(int shelf_id, int recipe_id);
};
#endif
