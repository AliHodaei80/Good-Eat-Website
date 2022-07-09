#include"person.hpp"

using namespace std;

Person::Person(string username_, string password_, string type_) {
    username = username_;
    password = password_;
    type = type_;
}
string Person::get_username() { return username; }
string Person::get_type() { return type; }
string Person::get_password() { return password; }