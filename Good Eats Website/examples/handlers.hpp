#ifndef HANDLER_H
#define HANDLER_H

#include<iostream>
#include"good_eat.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"

class check_login :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    check_login(Good_Eats* good);
    void check_information(std::string username, std::string password);
    Response* callback(Request* req);
};

class check_signup :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    check_signup(Good_Eats* good);
    void check_information(std::string username, std::string password, std::string type);
    Response* callback(Request* req);
};
class chef_page :public RequestHandler {
private:
    Good_Eats* good_eats;
    Server* server;
public:
    chef_page(Good_Eats* good_eats_, Server* server_);
    std::string creat_toolbar();
    Response* callback(Request* req);
};
class user_page :public RequestHandler {
private:
    Good_Eats* good_eats;
    Server* server;
public:
    user_page(Good_Eats* good_eats_, Server* server_);
    std::string creat_toolbar();
    std::string get_recipes();
    Response* callback(Request* req);
};
class add_recipe_handler :public RequestHandler {
    Good_Eats* good_eats;
public:
    add_recipe_handler(Good_Eats* good_eats_);
    void check_information(std::string title, std::string is_vegetarian, std::string image,
    std::string time,std::string ingredients, std::string tags);
    Response* callback(Request* req);
};
class delete_recipe_page :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    delete_recipe_page(Good_Eats* good_eats_);
    std::string creat_toolbar();
    Response* callback(Request* req);

};
class show_chef_recipes :public RequestHandler {
private:
    Good_Eats* good_eats;
    Server* server;
public:
    show_chef_recipes(Good_Eats* good_eats_, Server* server_);
    std::string creat_toolbar();
    Response* callback(Request* req);
};
class recipe_info :public RequestHandler {
private:
    Good_Eats* good_eats;
    Server* server;
public:
    recipe_info(Good_Eats* good_eats_, Server* server_);
    std::string creat_toolbar();
    Response* callback(Request* req);
};
class rating_recipe :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    rating_recipe(Good_Eats* good_eats_);
    void check_information(std::string recipe_id, std::string score);
    Response* callback(Request* req);
};
class manage_shelves :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    manage_shelves(Good_Eats* good_eats_);
    std::string get_my_shelves_link(std::vector<Shelf*>& my_shelves);
    std::string creat_toolbar();
    std::string add_shelf_button();
    std::string add_back_home_page();
    Response* callback(Request* req);
};
class add_shelf :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    add_shelf(Good_Eats* good_eats_);
    void check_information(std::string shelf_name);
    Response* callback(Request* req);
};
class shelf_managment :public RequestHandler {
private:
    Good_Eats* good_eats;
    Server* server;
public:
    shelf_managment(Good_Eats* good_eats_, Server* server_);
    std::string get_shelf_recipes(Shelf* shelf);
    std::string creat_toolbar();
    std::string creat_add_recipe(Shelf* shelf);
    std::string creat_delete_recipe(Shelf* shelf);
    Response* callback(Request* req);
};
class chenge_shelf_info :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    chenge_shelf_info(Good_Eats* good_eats_);
    Response* callback(Request* req);
};
class delete_recipe_handler :public RequestHandler {
private:
    Good_Eats* good_eats;
public:
    delete_recipe_handler(Good_Eats* good_eats_);
    Response* callback(Request* req);
};
class logout :public RequestHandler {
public:
    Response* callback(Request* req);
};
class Eror :public RequestHandler {
public:
    Response* callback(Request* req);
};

#endif // !HANDLER_H

