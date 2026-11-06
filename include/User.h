
#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {

private:
    string username;
    string password;

public:

    User(string username, string password);

    virtual ~User() = default;

    bool authenticate(string username, string password) const;

    string getUsername() const;

    string getPassword() const;

    virtual string getRole() const = 0;
};
