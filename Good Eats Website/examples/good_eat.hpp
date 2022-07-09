#ifndef GOOD_EAT_H
#define GOOD_EAT_H

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include"recipe.hpp"
#include"consts.hpp"
#include"person.hpp"
#include"chef.hpp"
#include"user.hpp"
#include"inputs.hpp"

class Good_Eats {
private:
    std::vector<Person*> people;
    std::vector<Shelf*> shelves;
    std::vector<Recipe*> recipes;
    std::vector<Recipe*> deleted_recipes;
    int deleted_recipe_num;
    Sorting_Objects sorting;
public:
    Good_Eats();
    ~Good_Eats();
    void add_recipe_to_shelf(std::string username, std::string shelf_id_, std::string recipe_id_);
    std::vector<Recipe*> get_all_recipes() { return recipes; }
    std::vector<Recipe*> get_recipes();
    Recipe* find_recipe(int id);
    std::vector<Shelf*> get_user_shelves(std::string username);
    Shelf* find_shelf(int id);
    void delete_shelves_recipes(std::string username, std::string shelf_id_, std::string recipe_id_);
    void delete_recipe(std::string username, std::string recipe_id);
    void add_recipe(std::string name, std::string title_, std::string vegeterian_,
        std::string image_addres_,std::string minutes, std::string tags_, std::string ingredients_);
    void rate_recipe(std::string username, std::string id_,
        std::string score_, std::string rated_before);
    void add_shelf(std::string username, std::string shelf_name);
    std::vector<Recipe*> get_not_added_recipes_from(Shelf* shelf);
    Person* find_person(std::string username);
    void login(std::string username, std::string password);
    void signup(std::string username, std::string password, std::string type);
    std::string get_all_upeople();
    int get_recipes_num();
};
#endif
