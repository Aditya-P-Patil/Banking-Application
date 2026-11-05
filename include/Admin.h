
#pragma once

#include "User.h"

class Admin : public User {

public:

    Admin(string username, string password);

    string getRole() const override;
};
