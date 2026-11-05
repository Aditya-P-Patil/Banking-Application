#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"

using namespace std;

class Bank {

private:

    vector<unique_ptr<Account>> accounts;

    int nextAccountNumber = 100001;

    // Private helper function
    Account* findAccount(int accNo);

public:

    // Account creation
    void createSavingsAccount(string name, long long amount);

    void createCurrentAccount(string name, long long amount);

    // Account management
    void displayAllAccounts();

    void searchAccount(int accNo);

    void updateAccount(int accNo, string newName);

    void closeAccount(int accNo);

    // Banking operations
    void depositMoney(int accNo, long long amount);

    void withdrawMoney(int accNo, long long amount);

    void checkBalance(int accNo);

    void showTransactionHistory(int accNo);
};
