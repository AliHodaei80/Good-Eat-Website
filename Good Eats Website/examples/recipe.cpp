#include"recipe.hpp"

using namespace std;

Recipe::Recipe(vector<string> ingredients_, vector<string> tags_, int id_, int minutes_to_ready_
    , string chef_name_, string title_, string image_addres_, string vegeterian_) {

    id = id_;
    minutes_to_ready = minutes_to_ready_;
    chef_name = chef_name_;
    title = title_;
    ingredients = ingredients_;
    tags = tags_;
    image_addres = image_addres_;
    vegeterian = vegeterian_;
    is_rated_ = false;
    if (vegeterian == "yes")
        is_vegetarian = true;
    else if (vegeterian == "no")
        is_vegetarian = false;
    rating = 0;
}
string Recipe::get_short_info() {
    ostringstream short_info;
    short_info << "Title: " << title << " Id: " << " " << id;
    return short_info.str();
}
int Recipe::find_user_rated(string user_rated) {
    for (int i = 0; i < static_cast<int>(scores.size()); i++)
        if (scores[i].rated_users_name == user_rated)
            return i;
    return INDEX_NOT_FOUND;
}
int Recipe::sum_of_grades() {
    int sum = 0;
    for (int i = 0; i < static_cast<int>(scores.size()); i++)
        sum += scores[i].score;
    return sum;
}
void Recipe::is_rating(int score, string user_rated) {
    is_rated_ = true;
    Scores new_score;
    new_score.rated_users_name = user_rated;
    new_score.score = score;
    scores.push_back(new_score);
    rating = ceil((sum_of_grades() * 1.0 / scores.size()) * 10) / 10;
}
bool Recipe::is_rated() { return is_rated_; }
void Recipe::delete_grade(string user_rated, int score) {
    int index = find_user_rated(user_rated);
    scores.erase(scores.begin() + index);
}
void Recipe::is_re_rating(int score, string user_rated) {
    if (find_user_rated(user_rated) == INDEX_NOT_FOUND)
        throw runtime_error(BAD_REQUEST_TXT);
    delete_grade(user_rated, score);
    Scores new_score;
    new_score.rated_users_name = user_rated;
    new_score.score = score;
    scores.push_back(new_score);
    rating = ceil((sum_of_grades() * 1.0 / scores.size()) * 10) / 10;
}
string Recipe::get_title() { return title; }
int Recipe::get_id() { return id; }
double Recipe::get_rating() { return rating; }
string Recipe::get_html_full_info() {
    ostringstream body;
    body
        << "<p>" << endl
        << "Id: " << id << "<br>" << endl
        << "Title: " << title << "<br>" << endl
        << "Minutes to ready: " << minutes_to_ready << "<br>" << endl
        << "Vegeterian: " << vegeterian << "<br>" << endl
        << "Tags: ";
    for (int i = 0; i < static_cast<int>(tags.size()); i++) {
        body << tags[i] << " ";
    }
    body << "<br>" << endl
        << "Ingredients: ";
    for (int i = 0; i < static_cast<int>(ingredients.size()); i++) {
        body << ingredients[i] << " ";
    }
    body
        << "<br>" << endl
        << "Rate: " << rating << "<br></p>" << endl;
    return body.str();
}
string Recipe::get_image() { return image_addres; }
string Recipe::get_html_short_info() {
    ostringstream body;
    body
        << "<p>" << endl
        << "Id: " << id << "<br>" << endl
        << "Title: " << title << "<br>" << endl
        << "Minutes to ready: " << minutes_to_ready << "<br>" << endl
        << "Vegeterian: " << vegeterian << "<br>" << endl
        << "</p>" << endl;
    return body.str();
}