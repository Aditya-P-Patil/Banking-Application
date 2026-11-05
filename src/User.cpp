
#include "User.h"

User::User(string username, string password) {

    this->username = username;
    this->password = password;
}

bool User::authenticate(string username, string password) const {

    return this->username == username &&
           this->password == password;
}

string User::getUsername() const {

    return username;
}
