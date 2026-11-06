#include <fstream>
#include <iomanip>
#include "Bank.h"
#include <iostream>

using namespace std;

Bank::Bank() {

    // Default admin account
    users.push_back(
        make_unique<Admin>("admin", "admin123")
    );

    // Load previously saved accounts
    loadAccounts();
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
    saveUsers();
    saveAccounts();

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
    saveUsers();
    saveAccounts();

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

    saveAccounts();

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

    saveUsers();
    saveAccounts();
}

// Deposit money
void Bank::depositMoney(int accNo, long long amount) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    long long previousBalance = acc->getBalance();

    acc->deposit(amount);

    if (acc->getBalance() != previousBalance) {
        saveAccounts();
    }
}

// Withdraw money
void Bank::withdrawMoney(int accNo, long long amount) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    long long previousBalance = acc->getBalance();

    acc->withdraw(amount);

    if (acc->getBalance() != previousBalance) {
        saveAccounts();
    }
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

    // 2. Prevent self-transfer
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

    // 4. Store sender's balance
    long long previousBalance = sender->getBalance();

    // 5. Withdraw money
    sender->withdraw(amount);

    // 6. Get the generated transaction ID
    int transactionId = sender->getLastTransactionId();

    // 7. Check whether withdrawal succeeded
    if (sender->getBalance() != previousBalance - amount) {

        sender->updateLastTransaction(
            "Transfer Sent",
            "FAILED",
            toAccNo,
            transactionId
        );

        cout << "Transfer failed!\n";
        return;
    }

    // 8. Update sender's transaction record
    sender->updateLastTransaction(
        "Transfer Sent",
        "SUCCESS",
        toAccNo,
        transactionId
    );

    // 9. Deposit money into receiver's account
    receiver->deposit(amount);

    // 10. Update receiver's transaction record
    receiver->updateLastTransaction(
        "Transfer Received",
        "SUCCESS",
        fromAccNo,
        transactionId
    );

    saveAccounts();

    cout << "\nTransfer successful!\n";
    cout << "Transaction ID: " << transactionId << "\n";
    cout << "Transferred Amount: Rs. " << amount << "\n";
    cout << "From Account: " << fromAccNo << "\n";
    cout << "To Account: " << toAccNo << "\n";
}

void Bank::showTransactionSummary(int accNo) {

    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "Account not found!\n";
        return;
    }

    acc->displayTransactionSummary();
}

void Bank::saveAccounts() {

    ofstream file("data/accounts.txt");

    if (!file.is_open()) {
        cout << "Error opening accounts file!\n";
        return;
    }

    for (auto& acc : accounts) {

        file << acc->getAccountType() << " "
             << acc->getAccountNumber() << " "
             << quoted(acc->getAccountHolder()) << " "
             << acc->getBalance() << "\n";
    }

    file.close();

    cout << "Accounts saved successfully!\n";
}

void Bank::loadAccounts() {

    ifstream file("data/accounts.txt");

    if (!file.is_open()) {
        cout << "No previous account data found!\n";
        return;
    }

    string type, name;
    int accNo;
    long long balance;

    while (file >> type >> accNo >> quoted(name) >> balance) {

        if (type == "Savings") {

            accounts.push_back(
                make_unique<SavingsAccount>(
                    accNo, name, balance
                )
            );
        }
        else if (type == "Current") {

            accounts.push_back(
                make_unique<CurrentAccount>(
                    accNo, name, balance
                )
            );
        }
        else {
            cout << "Unknown account type found!\n";
            continue;
        }

        // Update next available account number
        if (accNo >= nextAccountNumber) {
            nextAccountNumber = accNo + 1;
        }
    }

    file.close();

    cout << "Account data loaded successfully!\n";
}

void Bank::saveUsers() {

    ofstream file("data/users.txt");

    if (!file.is_open()) {
        cout << "Error opening users file!\n";
        return;
    }

    for (auto& user : users) {

        Customer* customer = dynamic_cast<Customer*>(user.get());

        if (customer != nullptr) {

            file << "Customer "
                 << quoted(customer->getUsername()) << " "
                 << quoted(customer->getPassword()) << " "
                 << customer->getAccountNumber() << "\n";
        }
    }

    file.close();

    cout << "User data saved successfully!\n";
}