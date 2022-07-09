#include<string>
#include <iostream>
#include"good_eat.hpp"
#include"handlers.hpp"
using namespace std;

int main() {

    string command_line;
    Good_Eats good_eats;
    Server server(8080);
    try {
        server.get("/", new ShowPage("static/home_page.html"));
        server.get("/home.css", new ShowFile("static/home.css", "text/css"));
        server.get("/fast-food.jpg", new ShowImage("static/fast-food.jpg"));
        server.get("/fast_food2.png", new ShowImage("static/fast_food2.png"));
        server.get("/Login", new ShowPage("static/login.html"));
        server.get("/login.css", new ShowFile("static/login.css", "text/css"));
        server.get("/Signup", new ShowPage("static/signup.html"));
        server.get("/signup.css", new ShowFile("static/signup.css", "text/css"));
        server.get("/login_page", new ShowPage("static/login_page.html"));
        server.get("/shelf.css", new ShowFile("static/shelf.css", "text/css"));
        server.get("/add_recipe_page.css", new ShowFile("static/add_recipe_page.css", "text/css"));
        server.post("/check_login", new check_login(&good_eats));
        server.post("/check_signup", new check_signup(&good_eats));
        server.get("/Login_chef", new chef_page(&good_eats, &server));
        server.get("/chef_page.css", new ShowFile("static/chef_page.css", "text/css"));
        server.get("/Login_user", new user_page(&good_eats, &server));
        server.get("/user_page.css", new ShowFile("static/user_page.css", "text/css"));
        server.get("/toolbar.css", new ShowFile("static/toolbar.css", "text/css"));
        server.get("/add_recipe_page", new ShowPage("static/add_recipe_page.html"));//delete_recipe.css
        server.get("/delete_recipe_page", new delete_recipe_page(&good_eats));///delete_recipe
        server.get("/delete_recipe.css", new ShowFile("static/delete_recipe.css", "text/css"));
        server.get("/delete_recipe", new delete_recipe_handler(&good_eats));
        server.post("/add_recipe", new add_recipe_handler(&good_eats));
        server.get("/show_chef_recipes", new show_chef_recipes(&good_eats, &server));//shw_chef_recipe
        server.get("/show_chef_recipe.css", new ShowFile("static/show_chef_recipe.css", "text/css"));
        server.get("/recipe_info", new recipe_info(&good_eats, &server));
        server.get("/recipe_info.css", new ShowFile("static/recipe_info.css", "text/css"));
        server.get("/recipe_rating", new rating_recipe(&good_eats));
        server.get("/manage_shelves", new manage_shelves(&good_eats));//manage_shelf
        server.get("/manage_shelf.css", new ShowFile("static/manage_shelf.css", "text/css"));
        server.get("/add_shelf_page", new ShowPage("static/add_shelf.html"));
        server.post("/add_shelf", new add_shelf(&good_eats));
        server.get("/shelf_managment", new shelf_managment(&good_eats, &server));
        server.get("/shelf_managment.css", new ShowFile("static/shelf_managment.css", "text/css"));
        server.get("/change_shelf_info", new chenge_shelf_info(&good_eats));
        server.get("/logout", new logout());
        server.get("/Eror", new Eror());
        server.get("/eror.css", new ShowFile("static/eror.css", "text/css"));
        server.run();
    }
    catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
    return 0;
}