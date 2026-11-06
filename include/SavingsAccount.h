
#pragma once

#include "Account.h"

class SavingsAccount : public Account {

private:
    double interestRate;
    long long minimumBalance = 1000;

public:

    SavingsAccount(int accNo, string name, long long initialBalance);

    double calculateInterest() override;

    void withdraw(long long amount) override;

    void displayDetails() override;

    string getAccountType() override;
};
