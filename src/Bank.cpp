
#include "Bank.h"
#include <iostream>

using namespace std;

// Private helper function
Account* Bank::findAccount(int accNo) {

    for (auto& acc : accounts) {

        if (acc->getAccountNumber() == accNo) {
            return acc.get();
        }
    }

    return nullptr;
}

// Create Savings Account
void Bank::createSavingsAccount(string name, long long amount) {

    if (name.empty() || amount < 0) {
        cout << "Invalid account details!\n";
        return;
    }

    accounts.push_back(
        make_unique<SavingsAccount>(
            nextAccountNumber, name, amount
        )
    );

    cout << "Savings Account created successfully!\n";
    cout << "Account Number: " << nextAccountNumber << "\n";

    nextAccountNumber++;
}

// Create Current Account
void Bank::createCurrentAccount(string name, long long amount) {

    if (name.empty() || amount < 0) {
        cout << "Invalid account details!\n";
        return;
    }

    accounts.push_back(
        make_unique<CurrentAccount>(
            nextAccountNumber, name, amount
        )
    );

    cout << "Current Account created successfully!\n";
    cout << "Account Number: " << nextAccountNumber << "\n";

    nextAccountNumber++;
}

// Display all accounts
void Bank::displayAllAccounts() {

    if (accounts.empty()) {
        cout << "No accounts registered yet!\n";
        return;
    }

    for (auto& acc : accounts) {
        acc->displayDetails();
    }
}

// Search account
void Bank::searchAccount(int accNo) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->displayDetails();
}

// Update account
void Bank::updateAccount(int accNo, string newName) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->updateName(newName);
}

// Close account
void Bank::closeAccount(int accNo) {

    for (auto it = accounts.begin(); it != accounts.end(); it++) {

        if ((*it)->getAccountNumber() == accNo) {

            if ((*it)->getBalance() != 0) {
                cout << "Account must have zero balance before closing!\n";
                return;
            }

            accounts.erase(it);

            cout << "Account closed successfully!\n";
            return;
        }
    }

    cout << "Account not found!\n";
}

// Deposit money
void Bank::depositMoney(int accNo, long long amount) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->deposit(amount);
}

// Withdraw money
void Bank::withdrawMoney(int accNo, long long amount) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->withdraw(amount);
}

// Check balance
void Bank::checkBalance(int accNo) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->checkBalance();
}

// Transaction history
void Bank::showTransactionHistory(int accNo) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->displayTransactionHistory();
}
