#include"inputs.hpp"

using namespace std;

vector<string> separating_words(string text, char disjunctive) {
    vector<string> words;
    stringstream line(text);
    while (line.good()) {
        string word;
        getline(line, word, disjunctive);
        words.push_back(word);
    }
    return words;
}