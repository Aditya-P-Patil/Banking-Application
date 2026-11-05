
#pragma once

#include "User.h"

class Customer : public User {

private:
    int accountNumber;

public:

    Customer(string username, string password, int accountNumber);

    string getRole() const override;

    int getAccountNumber() const;
};
