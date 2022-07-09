#ifndef SORTING_H
#define SORTING_H

#include<iostream>
#include<vector>
#include"recipe.hpp"
#include"person.hpp"

class Sorting_Objects {
public:
    std::vector<Recipe*> sorting_recipes(std::vector<Recipe*> unsorted_recipes);
    std::vector<Person*> sorting_people(std::vector<Person*> unsorted_people);
};
#endif

