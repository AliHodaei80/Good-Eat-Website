#include"handlers.hpp"

using namespace std;


check_login::check_login(Good_Eats* good) {
    good_eats = good;
}
void check_login::check_information(string username, string password) {
    if (username == EMPTY_TXT || password == EMPTY_TXT)
        throw runtime_error("Information incomplete");
}
Response* check_login::callback(Request* req) {
    try {
        string username = req->getBodyParam("name");
        string password = req->getBodyParam("password");
        check_information(username, password);
        good_eats->login(username, password);
        Person* want_login = good_eats->find_person(username);
        Response* res;
        if (want_login->get_type() == CHEF)
            res = Response::redirect("/Login_chef");
        else
            res = Response::redirect("/Login_user");
        res->setSessionId(username);
        return res;
    }
    catch (runtime_error& e) {
        Response* res;
        ostringstream body;
        body << "/Eror?eror=" << e.what();
        res = Response::redirect(body.str());
        return res;
    }
}


check_signup::check_signup(Good_Eats* good) {
    good_eats = good;
}
void check_signup::check_information(string username, string password, string type) {
    if (username == EMPTY_TXT || password == EMPTY_TXT || type == EMPTY_TXT)
        throw runtime_error("Information incomplete");
}
Response* check_signup::callback(Request* req) {
    string username = req->getBodyParam("name");
    string password = req->getBodyParam("password");
    string type = req->getBodyParam("type");
    try {
        check_information(username, password, type);
        good_eats->signup(username, password, type);
        Person* want_signup = good_eats->find_person(username);
        Response* res;
        if (want_signup->get_type() == CHEF)
            res = Response::redirect("/Login_chef");
        else
            res = Response::redirect("/Login_user");
        res->setSessionId(username);
        return res;
    }
    catch (runtime_error& e) {
        Response* res;
        ostringstream body;
        body << "/Eror?eror=" << e.what();
        res = Response::redirect(body.str());
        return res;
    }
}

chef_page::chef_page(Good_Eats* good_eats_, Server* server_) {
    good_eats = good_eats_;
    server = server_;
}
string chef_page::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_chef'>Home</a>" << endl
        << "<a href='/add_recipe_page'>Add recipe</a>" << endl
        << "<a href='/delete_recipe_page'>delete recipe</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
Response* chef_page::callback(Request* req) {
    Response* res = new Response;
    string username = req->getSessionId();
    vector<Recipe*> recipes = good_eats->find_person(username)->get_my_recipes();
    res->setHeader("Content-type", "text/html");
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<title>Good Eats</title>" << endl
        << "<link rel='stylesheet' type='text/css' href='chef_page.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>" << "Welcome Chef " << req->getSessionId() << "</h2>" << endl
        << "<div class='main'>" << endl
        << "<h3> YOUR RECIPES</h3><br>" << endl;
    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        body
            << "<div class='recipe'>" << endl
            << "<img class='image' src='" << recipes[i]->get_image() << "'><br>" << endl
            << recipes[i]->get_html_full_info() << "</div>" << endl;
        ostringstream body1, body2;
        body1 << "/" << recipes[i]->get_image();
        body2 << "images/" << recipes[i]->get_image();
        server->get(body1.str(), new ShowImage(body2.str()));
    }
    body
        << "<form action='/logout' method='get'>" << endl
        << "<div class='links'>" << endl
        << "<h3><a href='add_recipe_page'>add recipe</a></h3><br>" << endl
        << "<h3><a href='show_chef_recipes'>show recipe</a></h3><br>" << endl
        << "<h3><a href='delete_recipe_page'>delete recipe</a></h3><br>" << endl
        << "<br><br><input class='in3' type='submit' value='logout'>" << endl
        << "</form>" << endl
        << "</div></div>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

user_page::user_page(Good_Eats* good_eats_, Server* server_) {
    good_eats = good_eats_;
    server = server_;
}
string user_page::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_user'>Home</a>" << endl
        << "<a href='/add_shelf_page'>Add shelf</a>" << endl
        << "<a href='/manage_shelves'>Manage shelves</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}

string user_page::get_recipes() {
    vector<Recipe*> recipes = good_eats->get_all_recipes();
    ostringstream body;

    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        body
            << "<div class='recipe'>"
            << "<a href='/recipe_info?id=" << recipes[i]->get_id() << "'>"
            << "<img class='image' src='" << recipes[i]->get_image() << "'>" << "</a><br><br>"
            << recipes[i]->get_html_short_info() << endl
            << "</div>" << endl;
        ostringstream body1, body2;
        body1 << "/" << recipes[i]->get_image();
        body2 << "images/" << recipes[i]->get_image();
        server->get(body1.str(), new ShowImage(body2.str()));
    }
    return body.str();

}

Response* user_page::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<title>Good Eats</title>" << endl
        << "<link rel='stylesheet' type='text/css' href='user_page.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>" << "Welcome User " << req->getSessionId() << "</h2>" << endl
        << "<form action='/logout' method='get'>" << endl
        << "<br>" << endl
        << "<h3> Recipes</h3>" << endl
        << get_recipes() << "<br><br>" << endl
        << "<h3><a href='/manage_shelves'> Manage my shelves</a></h3><br>" << endl
        << "<input class='in3' type='submit' value='logout'>" << endl
        << "</form>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

add_recipe_handler::add_recipe_handler(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
void add_recipe_handler::add_recipe_handler::check_information(string title, string is_vegetarian,
                                     string image, string time,string ingredients, string tags) {
    if (title == EMPTY_TXT || is_vegetarian == EMPTY_TXT || image == EMPTY_TXT ||
        time == EMPTY_TXT || ingredients == EMPTY_TXT || tags == EMPTY_TXT)
        throw runtime_error("Information incomplete");
}
Response* add_recipe_handler::callback(Request* req) {
    try {
        string title = req->getBodyParam("title");
        string is_vegetarian = req->getBodyParam("is_vegeterian");
        string image = req->getBodyParam("img");
        string time = req->getBodyParam("time");
        string ingredients = req->getBodyParam("ingredients");
        string tags = req->getBodyParam("tags");
        check_information(title, is_vegetarian, image, time, ingredients, tags);
        good_eats->add_recipe(req->getSessionId(), title, is_vegetarian,
            image, time, tags, ingredients);
        Response* res = Response::redirect("/Login_chef");
        return res;
    }
    catch (runtime_error& e) {
        Response* res;
        ostringstream body;
        body << "/Eror?eror=" << e.what();
        res = Response::redirect(body.str());
        return res;
    }
}

delete_recipe_page::delete_recipe_page(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
string delete_recipe_page::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_chef'>Home</a>" << endl
        << "<a href='/add_recipe_page'>Add recipe</a>" << endl
        << "<a href='/delete_recipe_page'>delete recipe</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
Response* delete_recipe_page::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    vector<Recipe*>recipes = good_eats->find_person(req->getSessionId())->get_my_recipes();
    ostringstream body;
    body << "<html>" << endl
        << "<title>Good Eats</title>" << endl
        << "<link rel='stylesheet' type='text/css' href='delete_recipe.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>DELETE RECIPE</h2><br>" << endl
        << "<div class='delete'>" << endl
        << "<p>Select recipe you want to delete:<br></p>" << endl
        << "<form action='/delete_recipe' method='get'>" << endl
        << "<select class='recipes' name='deleted_recipe'>" << endl
        << "<option value='None'>None</option>" << endl;
    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        body << "<option value='" << recipes[i]->get_id() << "'>"
            << recipes[i]->get_short_info() << "</option>" << endl;
    }
    body << "</select><br><br>" << endl
        << "<input class='in3' type='submit' value='submit'>" << endl
        << "</form>" << endl
        << "</div>" << endl
        << "</body>" << endl
        << "</html>";
    res->setBody(body.str());
    return res;
}

show_chef_recipes::show_chef_recipes(Good_Eats* good_eats_, Server* server_) {
    good_eats = good_eats_;
    server = server_;
}
string show_chef_recipes::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_chef'>Home</a>" << endl
        << "<a href='/add_recipe_page'>Add recipe</a>" << endl
        << "<a href='/delete_recipe_page'>delete recipe</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
Response* show_chef_recipes::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    string username = req->getSessionId();
    vector<Recipe*> recipes = good_eats->find_person(username)->get_my_recipes();
    ostringstream body;
    body
        << "<html>" << endl
        << "<title>Good Eats</title>"
        << "<link rel='stylesheet' type='text/css' href='show_chef_recipe.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<div class='main'>" << endl
        << "<br><br><h2> YOUR RECIPES</h2><br>" << endl;
    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        body
            << "<div class='recipe'>" << endl
            << "<img class='image' src='" << recipes[i]->get_image() << "'><br>" << endl
            << recipes[i]->get_html_full_info() << "</div>" << endl;
        ostringstream body1, body2;
        body1 << "/" << recipes[i]->get_image();
        body2 << "images/" << recipes[i]->get_image();
        server->get(body1.str(), new ShowImage(body2.str()));
    }
    body
        << "<br><script>"
        << "function goBack(){" << endl
        << "window.history.back()" << endl
        << "}" << endl
        << "</script>" << endl
        << "<button class='in3' onclick='goBack()'>Go Back</button>" << endl
        << "</div>"
        << "</body>" << endl
        << "</html>";
    res->setBody(body.str());
    return res;

}

recipe_info::recipe_info(Good_Eats* good_eats_, Server* server_) {
    good_eats = good_eats_;
    server = server_;
}
string recipe_info::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_user'>Home</a>" << endl
        << "<a href='/add_shelf_page'>Add shelf</a>" << endl
        << "<a href='/manage_shelves'>Manage shelves</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
Response* recipe_info::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");

    string logged_in_user = req->getSessionId();
    Recipe* recipe = good_eats->find_recipe(stoi(req->getQueryParam("id")));
    ostringstream body;
    body
        << "<html>" << endl
        << "<title>Good Eats</title>"
        << "<link rel='stylesheet' type='text/css' href='recipe_info.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>RECIPE INFO</h2><br>" << endl
        << "<div class='recipe'>" << endl
        << "<img class='image' src='" << recipe->get_image() << "'><br>" << endl;
    ostringstream body1, body2;
    body1 << "/" << recipe->get_image();
    body2 << "images/" << recipe->get_image();
    server->get(body1.str(), new ShowImage(body2.str()));
    body
        << recipe->get_html_full_info() << endl
        << "<form action='/recipe_rating'>" << endl
        << "<input type='hidden' name='recipe_id' value='" << recipe->get_id() << "'>" << endl
        << "</div>" << endl
        << "<div class='score'>" << endl
        << "<p>" << "Score you gave: ";
    int user_index_rating = recipe->find_user_rated(req->getSessionId());
    if (user_index_rating != INDEX_NOT_FOUND) {
        body << recipe->get_user_rating(user_index_rating) << "</p><br>" << endl
            << "<input type='hidden' name='rated_before' value='yes'>";
    }
    else {
        body << "You didn't" << "</p><br>" << endl
            << "<input type='hidden' name='rated_before' value='no'>";
    }
    body
        << "<select name='score' class='score'>" << endl;
    for (int i = 1; i < 6; i++)
        body << "<option value='" << i << "'>" << i << "</option>" << endl;
    body
        << "</select><br>" << endl
        << "<br><input class='in3' type='submit' value='submit'>" << endl
        << "</div>"
        << "</form>" << endl
        << "<script>" << endl
        << "function goBack(){" << endl
        << "window.history.back()"
        << "}" << endl
        << "</script>" << endl
        << "<br><br><button class='in3' onclick='goBack()'>Go Back</button>" << endl
        << "</body>" << endl
        << "</htm>";
    res->setBody(body.str());
    return res;
}

rating_recipe::rating_recipe(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
void rating_recipe::check_information(string recipe_id, string score) {
    if (recipe_id == EMPTY_TXT || score == EMPTY_TXT)
        throw runtime_error("Information incomplete");
}
Response* rating_recipe::callback(Request* req) {
    try {
        string logged_in_user = req->getSessionId();
        string recipe_id = req->getQueryParam("recipe_id");
        string score = req->getQueryParam("score");
        string rated_before = req->getQueryParam("rated_before");
        check_information(recipe_id, score);
        good_eats->rate_recipe(req->getSessionId(), recipe_id, score, rated_before);
        Response* res = Response::redirect("/Login_user");
        return res;
    }
    catch (runtime_error& e) {
        Response* res;
        ostringstream body;
        body << "/Eror?eror=" << e.what();
        res = Response::redirect(body.str());
        return res;
    }
}

manage_shelves::manage_shelves(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
string manage_shelves::get_my_shelves_link(vector<Shelf*>& my_shelves) {
    ostringstream body;
    for (int i = 0; i < static_cast<int>(my_shelves.size()); i++) {
        body << "<a href='/shelf_managment?id=" << my_shelves[i]->get_id() << "'>"
            << "name: " << my_shelves[i]->get_name() << " id: "
            << my_shelves[i]->get_id() << "</a>" << "<br>" << endl;
    }
    return body.str();
}
string manage_shelves::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_user'>Home</a>" << endl
        << "<a href='/add_shelf_page'>Add shelf</a>" << endl
        << "<a href='/manage_shelves'>Manage shelves</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
string manage_shelves::add_shelf_button() {
    ostringstream body;
    body
        << "<form action='/add_shelf_page' method='get'>" << endl
        << "<input class='in4' type='submit' value='Add new shelf'>" << endl
        << "</form>" << endl;
    return body.str();
}
string manage_shelves::add_back_home_page() {
    ostringstream body;
    body
        << "<form action='/Login_user' method='get'>" << endl
        << "<input class='in4' type='submit' value='back to home'>" << endl
        << "</form>" << endl;
    return body.str();
}
Response* manage_shelves::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    string logged_in_user = req->getSessionId();
    vector<Shelf*> my_shelves = good_eats->get_user_shelves(logged_in_user);
    ostringstream body;
    body
        << "<html>" << endl
        << "<link rel='stylesheet' type='text/css' href='manage_shelf.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>My shelves</h2>" << endl
        << "<div class='main'>" << endl
        << get_my_shelves_link(my_shelves) << "<br>" << endl
        << add_shelf_button() << "<br>" << endl
        << add_back_home_page() << "<br>" << endl
        << "</div>" << endl
        << "</body>" << endl
        << "</html>";
    res->setBody(body.str());
    return res;
}

add_shelf::add_shelf(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
void add_shelf::check_information(string shelf_name) {
    if (shelf_name == EMPTY_TXT)
        throw runtime_error("Information incomplete");
}
Response* add_shelf::callback(Request* req) {
    try {
        string logged_in_user = req->getSessionId();
        string shelf_name = req->getBodyParam("shelf_name");
        check_information(shelf_name);
        good_eats->add_shelf(logged_in_user, shelf_name);
        Response* res = Response::redirect("/manage_shelves");
        return res;
    }
    catch (runtime_error& e) {
        Response* res;
        ostringstream body;
        body << "/Eror?eror=" << e.what();
        res = Response::redirect(body.str());
        return res;
    }
}

shelf_managment::shelf_managment(Good_Eats* good_eats_, Server* server_) {
    good_eats = good_eats_;
    server = server_;
}
string shelf_managment::get_shelf_recipes(Shelf* shelf) {
    vector<Recipe*> recipes = shelf->get_recipes();
    ostringstream body;

    for (int i = 0; i < static_cast<int>(recipes.size()); i++) {
        body
            << "<div class='recipe'>"
            << "<a href='/recipe_info?id=" << recipes[i]->get_id() << "'>"
            << "<img class='image' src='" << recipes[i]->get_image() << "'>" << "</a><br><br>"
            << recipes[i]->get_html_short_info() << endl
            << "</div>" << endl;
        ostringstream body1, body2;
        body1 << "/" << recipes[i]->get_image();
        body2 << "images/" << recipes[i]->get_image();
        server->get(body1.str(), new ShowImage(body2.str()));
    }
    return body.str();

}
string shelf_managment::creat_toolbar() {
    ostringstream body;
    body
        << "<div class='icon-bar'>" << endl
        << "<a class='active' href='/Login_user'>Home</a>" << endl
        << "<a href='/add_shelf_page'>Add shelf</a>" << endl
        << "<a href='/manage_shelves'>Manage shelves</a>" << endl
        << "<a href='/logout'>Logout</a>" << endl
        << "</div>" << endl;
    return body.str();
}
string shelf_managment::creat_add_recipe(Shelf* shelf) {
    vector<Recipe*> not_added_recipes = good_eats->get_not_added_recipes_from(shelf);
    ostringstream body;
    body
        << "<br><div class='add'>" << endl
        << "<p>" << endl
        << "Add recipe to your shelf:<br>" << endl
        << "</p>" << endl
        << "<select class='recipes' name='added_recipe'>" << endl
        << "<option value='None'>None</option>" << endl;
    for (int i = 0; i < static_cast<int>(not_added_recipes.size()); i++) {
        body << "<option value='" << not_added_recipes[i]->get_id() << "'>"
            << not_added_recipes[i]->get_short_info() << "</option>" << endl;
    }
    body << "</select>" << endl
        << "</div>" << endl;
    return body.str();

}
string shelf_managment::creat_delete_recipe(Shelf* shelf) {
    vector<Recipe*> added_recipes = shelf->get_recipes();
    ostringstream body;
    body
        << "<div class='delete'>" << endl
        << "<p>" << endl
        << "Delete recipe from your shelf:<br>" << endl
        << "</p>" << endl
        << "<select name='deleted_recipe' class='recipes'>" << endl
        << "<option value='None'>None</option>" << endl;
    for (int i = 0; i < static_cast<int>(added_recipes.size()); i++) {
        body << "<option value='" << added_recipes[i]->get_id() << "'>"
            << added_recipes[i]->get_short_info() << "</option>" << endl;
    }
    body << "</select>" << endl
        << "</div>" << endl;
    return body.str();

}
Response* shelf_managment::callback(Request* req) {
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    string logged_in_user = req->getSessionId();
    string shelf_id = req->getQueryParam("id");
    Shelf* shelf = good_eats->find_shelf(stoi(shelf_id));
    ostringstream body;
    body
        << "<html>" << endl
        << "<link rel='stylesheet' type='text/css' href='shelf_managment.css'>" << endl
        << "<link rel='stylesheet' type='text/css' href='toolbar.css'>" << endl
        << "<body>" << endl
        << creat_toolbar()
        << "<br><br><h2>My shelf</h2>" << endl
        << "<div class='main'>" << endl
        << "<h3>name: " << shelf->get_name() << " id: " << shelf->get_id() << endl
        << "<form action='/change_shelf_info' methode='get'>" << endl
        << "<input type='hidden' name='shelf_id' value='" << shelf->get_id() << "'>" << endl
        << get_shelf_recipes(shelf) << "</div><br>" << endl
        << creat_add_recipe(shelf) << "<br>" << endl
        << creat_delete_recipe(shelf) << "<br>" << endl
        << "<input class='in3' type='submit' value='submit'>" << endl
        << "</form>" << endl
        << "<script>" << endl
        << "function goBack(){" << endl
        << "window.history.back()"
        << "}" << endl
        << "</script>" << endl
        << "<br><br><button class='in3' onclick='goBack()'>Go Back</button>" << endl
        << "</body>" << endl
        << "<html>";
    res->setBody(body.str());
    return res;
}

chenge_shelf_info::chenge_shelf_info(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
Response* chenge_shelf_info::callback(Request* req) {
    string logged_in_user = req->getSessionId();
    string shelf_id = req->getQueryParam("shelf_id");
    string deleted_recipe_id = req->getQueryParam("deleted_recipe");
    string added_recipe_id = req->getQueryParam("added_recipe");
    if (added_recipe_id != "None") {
        good_eats->add_recipe_to_shelf(logged_in_user, shelf_id, added_recipe_id);
    }
    if (deleted_recipe_id != "None") {
        good_eats->delete_shelves_recipes(logged_in_user, shelf_id, deleted_recipe_id);
    }
    ostringstream link;
    link
        << "/shelf_managment?id=" << shelf_id;
    Response* res = Response::redirect(link.str());
    return res;
}

delete_recipe_handler::delete_recipe_handler(Good_Eats* good_eats_) {
    good_eats = good_eats_;
}
Response* delete_recipe_handler::callback(Request* req) {
    string recipe_id = req->getQueryParam("deleted_recipe");
    if (recipe_id != "None")
        good_eats->delete_recipe(req->getSessionId(), recipe_id);
    Response* res = Response::redirect("/Login_chef");
    return res;
}
Response* logout::callback(Request* req) {
        Response* res = Response::redirect("/");
        return res;
    }
Response* Eror::callback(Request* req) {
    string eror = "Eror happend.";
    eror = req->getQueryParam("eror");
    Response* res = new Response;
    res->setHeader("Content-type", "text/html");
    ostringstream body;
    body
        << "<!DOCTYPE html>" << endl
        << "<html>" << endl
        << "<link rel='stylesheet' type='text/css' href='eror.css'>" << endl
        << "<body>" << endl
        << "<br><br><br>" << endl
        << "<h1>" << eror << "</h1><br><br>" << endl
        << "<button class='in4' onclick='goBack()'>Go Back</button>" << endl
        << "<script>" << endl
        << "function goBack() {" << endl
        << "window.history.back();" << endl
        << "}" << endl
        << "</script>" << endl
        << "</body>" << endl
        << "</html>" << endl;
    res->setBody(body.str());
    return res;
}