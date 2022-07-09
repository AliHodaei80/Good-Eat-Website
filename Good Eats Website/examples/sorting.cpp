#include"sorting.hpp"

using namespace std;

vector<Recipe*> Sorting_Objects::sorting_recipes(vector<Recipe*> unsorted_recipes) {
    bool sorted = true;
    while (true) {
        sorted = true;
        for (int i = 0; i < static_cast<int>(unsorted_recipes.size()) - 1; i++) {
            if (unsorted_recipes[i]->get_title().compare(unsorted_recipes[i + 1]->get_title()) > 0) {
                swap(unsorted_recipes[i], unsorted_recipes[i + 1]);
                sorted = false;
            }
        }
        if (sorted)
            break;
    }
    return unsorted_recipes;
}
vector<Person*> Sorting_Objects::sorting_people(vector<Person*> unsorted_people) {
    bool sorted = true;
    while (true) {
        sorted = true;
        for (int i = 0; i < static_cast<int>(unsorted_people.size()) - 1; i++) {
            if (unsorted_people[i]->get_username().compare(unsorted_people[i + 1]->get_username()) > 0) {
                swap(unsorted_people[i], unsorted_people[i + 1]);
                sorted = false;
            }
        }
        if (sorted)
            break;
    }
    return unsorted_people;
}