
#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank() {

    // Default admin account
    users.push_back(
        make_unique<Admin>("admin", "admin123")
    );
}

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
int Bank::createSavingsAccount(
    string name,
    long long amount,
    string username,
    string password
) {

    if (name.empty() || username.empty() ||
        password.empty() || amount < 0) {

        cout << "Invalid registration details!\n";
        return -1;
    }

    if (usernameExists(username)) {
        cout << "Username already exists!\n";
        return -1;
    }

    int accNo = nextAccountNumber;

    accounts.push_back(
        make_unique<SavingsAccount>(accNo, name, amount)
    );

    users.push_back(
        make_unique<Customer>(username, password, accNo)
    );

    nextAccountNumber++;

    cout << "\nSavings Account created successfully!\n";
    cout << "Account Number: " << accNo << "\n";
    cout << "Username: " << username << "\n";

    return accNo;
}

// Create Current Account
int Bank::createCurrentAccount(
    string name,
    long long amount,
    string username,
    string password
) {

    if (name.empty() || username.empty() ||
        password.empty() || amount < 0) {

        cout << "Invalid registration details!\n";
        return -1;
    }

    if (usernameExists(username)) {
        cout << "Username already exists!\n";
        return -1;
    }

    int accNo = nextAccountNumber;

    accounts.push_back(
        make_unique<CurrentAccount>(accNo, name, amount)
    );

    users.push_back(
        make_unique<Customer>(username, password, accNo)
    );

    nextAccountNumber++;

    cout << "\nCurrent Account created successfully!\n";
    cout << "Account Number: " << accNo << "\n";
    cout << "Username: " << username << "\n";

    return accNo;
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

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    if (acc->getBalance() != 0) {
        cout << "Account must have zero balance before closing!\n";
        return;
    }

    // Remove the account
    for (auto it = accounts.begin(); it != accounts.end(); it++) {

        if ((*it)->getAccountNumber() == accNo) {
            accounts.erase(it);
            break;
        }
    }

    // Remove the associated customer
    for (auto it = users.begin(); it != users.end(); it++) {

        Customer* customer = dynamic_cast<Customer*>(it->get());

        if (customer != nullptr &&
            customer->getAccountNumber() == accNo) {

            users.erase(it);
            break;
        }
    }

    cout << "Account closed successfully!\n";
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

bool Bank::usernameExists(string username) {

    for (auto& user : users) {

        if (user->getUsername() == username) {
            return true;
        }
    }

    return false;
}

User* Bank::authenticateUser(string username, string password) {

    for (auto& user : users) {

        if (user->authenticate(username, password)) {
            return user.get();
        }
    }

    return nullptr;
}

void Bank::transferMoney(int fromAccNo, int toAccNo, long long amount) {

    // 1. Validate amount
    if (amount <= 0) {
        cout << "Invalid transfer amount!\n";
        return;
    }

    // 2. Prevent transferring to the same account
    if (fromAccNo == toAccNo) {
        cout << "Cannot transfer to the same account!\n";
        return;
    }

    // 3. Find both accounts
    Account* sender = findAccount(fromAccNo);
    Account* receiver = findAccount(toAccNo);

    if (sender == nullptr || receiver == nullptr) {
        cout << "One or both accounts do not exist!\n";
        return;
    }

    // 4. Store sender's balance before withdrawal
    long long previousBalance = sender->getBalance();

    // 5. Withdraw from sender
    sender->withdraw(amount);

    // 6. Check whether withdrawal was successful
    if (sender->getBalance() != previousBalance - amount) {
        cout << "Transfer failed!\n";
        return;
    }

    // 7. Deposit into receiver
    receiver->deposit(amount);

    cout << "\nTransfer successful!\n";
    cout << "Transferred Amount: Rs. " << amount << "\n";
    cout << "From Account: " << fromAccNo << "\n";
    cout << "To Account: " << toAccNo << "\n";
}