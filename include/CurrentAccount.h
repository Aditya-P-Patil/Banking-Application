
#pragma once

#include "Account.h"

class CurrentAccount : public Account {

public:

    CurrentAccount(int accNo, string name, long long initialBalance);

    double calculateInterest() override;

    void withdraw(long long amount) override;

    void displayDetails() override;

    string getAccountType() override;
};
