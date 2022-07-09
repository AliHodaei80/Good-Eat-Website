#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<vector>
#include"consts.hpp"

class Recipe;
class Shelf;
class Person {
protected:
    std::string username;
    std::string password;
    std::string type;
public:
    Person(std::string username_, std::string password_, std::string type_);
    virtual ~Person() {};
    std::string get_username();
    std::string get_type();
    std::string get_password();
    virtual Recipe* add_recipe(std::string title_, std::string vegeterian_, std::string image_addres_,
        std::string minutes, std::string tags_, std::string ingredients_, int id) = 0;
    virtual void add_new_shelf(std::string name, int id) = 0;
    virtual Shelf* get_new_shelf() = 0;
    virtual std::vector<Shelf*> get_shelves() = 0;
    virtual void add_recipe_to_shelf(int shelf_id, Recipe* recipe) = 0;
    virtual void delete_recipe_from_shelf(int shelf_id, int recipe_id) = 0;
    virtual double get_rating() = 0;
    virtual void delete_recipe(int id, std::vector<Recipe*>& all_recipes, std::vector<Recipe*>& deleted_recipes) = 0;
    virtual std::vector<Recipe*> get_my_recipes() = 0;
};
#endif