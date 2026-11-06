#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "User.h"
#include "Admin.h"
#include "Customer.h"

using namespace std;

class Bank {

private:

    vector<unique_ptr<Account>> accounts;
    vector<unique_ptr<User>> users;

    int nextAccountNumber = 100001;

    Account* findAccount(int accNo);

    bool usernameExists(string username);

public:
    Bank();

    // Authentication
    User* authenticateUser(string username, string password);

    // Customer registration
    int createSavingsAccount(
        string name, long long amount,
        string username, string password
    );

    int createCurrentAccount(
        string name, long long amount,
        string username, string password
    );

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

    void transferMoney(int fromAccNo, int toAccNo, long long amount);

    void showTransactionSummary(int accNo);
};
