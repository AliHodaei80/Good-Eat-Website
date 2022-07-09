#ifndef RECIPE_H
#define RECIPE_H

#include<iostream>
#include<vector>
#include<fstream>
#include <sstream>
#include<math.h>
#include"consts.hpp"


struct Scores {
    std::string rated_users_name;
    int score;
};
class Recipe {
private:
    int id;
    int minutes_to_ready;
    std::string chef_name;
    std::string title;
    std::vector<std::string> ingredients;
    std::string vegeterian;
    bool is_vegetarian;
    std::vector<std::string> tags;
    std::string image_addres;
    double rating;
    bool is_rated_;
    std::vector<Scores> scores;
public:

    Recipe(std::vector<std::string> ingredients_, std::vector<std::string> tags_, int id_, int minutes_to_ready_
        , std::string chef_name_, std::string title_, std::string image_addres_, std::string vegeterian_);
    std::string get_short_info();
    int get_user_rating(int index) { return scores[index].score; }
    int find_user_rated(std::string user_rated);
    int sum_of_grades();
    void is_rating(int score, std::string user_rated);
    bool is_rated();
    void delete_grade(std::string user_rated, int score);
    void is_re_rating(int score, std::string user_rated);
    std::string get_title();
    int get_id();
    double get_rating();
    std::string get_image();
    std::string get_html_full_info();
    std::string get_html_short_info();
};
#endif
