#ifndef USER_H
#define USER_H

#include<iostream>
#include<vector>
#include"person.hpp"
#include"shelf.hpp"

class User :public Person {
private:
    std::vector<Shelf*> my_shelves;
public:
    User(std::string username_, std::string password_, std::string type_);
    Shelf* find_shelf(int id);
    void add_recipe_to_shelf(int shelf_id, Recipe* recipe);
    virtual Recipe* add_recipe(std::string title_, std::string vegeterian_, std::string image_addres_,
        std::string minutes, std::string tags_, std::string ingredients_, int id);
    virtual void add_new_shelf(std::string name, int id);
    virtual Shelf* get_new_shelf();
    std::vector<Shelf*> get_shelves();
    void delete_recipe_from_shelf(int shelf_id, int recipe_id);
    double get_rating();
    void delete_recipe(int id, std::vector<Recipe*>& all_recipes,
        std::vector<Recipe*>& deleted_recipes);
    std::vector<Recipe*> get_my_recipes();
};
#endif
