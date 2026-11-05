
#include "Admin.h"

Admin::Admin(string username, string password)
    : User(username, password) {
}

string Admin::getRole() const {

    return "Admin";
}
