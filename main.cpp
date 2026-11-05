#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

struct Transaction {
    string type;
    long long amount;
    string status;
};


class Account {

protected:
    int accountNumber;
    string accountHolder;
    long long balance;

    vector<Transaction> transactions;

public:

    Account(int accNo, string name, long long initialBalance) {
        accountNumber = accNo;
        accountHolder = name;
        balance = initialBalance;
    }

    // Virtual destructor
    virtual ~Account() = default;

    int getAccountNumber() {
        return accountNumber;
    }

    long long getBalance() {
        return balance;
    }

    void updateName(string newName) {
        if (newName.empty()) {
            cout << "Name cannot be empty!\n";
            return;
        }

        accountHolder = newName;
        cout << "Name updated successfully!\n";
    }

    void deposit(long long amount) {

        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            transactions.push_back({"Deposit", amount, "FAILED"});
            return;
        }

        balance += amount;
        transactions.push_back({"Deposit", amount, "SUCCESS"});

        cout << "Amount deposited successfully!\n";
    }

    virtual void withdraw(long long amount) {

        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            transactions.push_back({"Withdrawal", amount, "FAILED"});
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            transactions.push_back({"Withdrawal", amount, "FAILED"});
            return;
        }

        balance -= amount;
        transactions.push_back({"Withdrawal", amount, "SUCCESS"});

        cout << "Amount withdrawn successfully!\n";
    }

    void checkBalance() {
        cout << "Current Balance: Rs. " << balance << "\n";
    }

    virtual void displayDetails() {
        cout << "\n----- ACCOUNT DETAILS -----\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Account Holder : " << accountHolder << "\n";
        cout << "Balance        : Rs. " << balance << "\n";
    }

    void displayTransactionHistory() {

        if (transactions.empty()) {
            cout << "No transactions available!\n";
            return;
        }

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        for (int i = 0; i < transactions.size(); i++) {
            cout << "\nTransaction " << i + 1 << "\n";
            cout << "Type   : " << transactions[i].type << "\n";
            cout << "Amount : Rs. " << transactions[i].amount << "\n";
            cout << "Status : " << transactions[i].status << "\n";
        }
    }

    // Pure virtual function
    virtual double calculateInterest() = 0;
};


class SavingsAccount : public Account {

private:
    double interestRate;

public:

    SavingsAccount(int accNo, string name, long long initialBalance)
        : Account(accNo, name, initialBalance) {

        interestRate = 4.0;
    }

    double calculateInterest() override {

        return balance * interestRate / 100.0;
    }

    void displayDetails() override {

        Account::displayDetails();

        cout << "Account Type   : Savings Account\n";
        cout << "Interest Rate  : " << interestRate << "%\n";
        cout << "Interest       : Rs. " << calculateInterest() << "\n";
    }
};


class CurrentAccount : public Account {

public:

    CurrentAccount(int accNo, string name, long long initialBalance)
        : Account(accNo, name, initialBalance) {
    }

    double calculateInterest() override {

        return 0;
    }

    void displayDetails() override {

        Account::displayDetails();

        cout << "Account Type   : Current Account\n";
        cout << "Interest       : Not Applicable\n";
    }
};

int findAccount(vector<Account>& accounts, int accNo) {

    for (int i = 0; i < accounts.size(); i++) {

        if (accounts[i].getAccountNumber() == accNo) {
            return i;
        }
    }

    return -1;
}

void closeAccount(vector<Account>& accounts, int accNo) {

    int index = findAccount(accounts, accNo);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    if (accounts[index].getBalance() != 0) {
        cout << "Account must have zero balance before closing!\n";
        return;
    }

    accounts.erase(accounts.begin() + index);

    cout << "Account closed successfully!\n";
}


int main() {

    vector<unique_ptr<Account>> accounts;

    int nextAccountNumber = 100001;
    int choice, accNo;
    long long amount;
    string name;

    while (true) {

        cout << "\n========== BANKSPHERE ==========\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Update Account Details\n";
        cout << "7. Close Account\n";
        cout << "8. Transaction History\n";
        cout << "9. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {

                cout << "Enter account holder name: ";
                getline(cin >> ws, name);

                cout << "Enter initial balance: ";
                cin >> amount;

                if (amount < 0) {
                    cout << "Invalid initial balance!\n";
                    break;
                }

                Account newAccount(nextAccountNumber, name, amount);

                accounts.push_back(newAccount);

                cout << "\nAccount created successfully!\n";
                cout << "Your Account Number: " << nextAccountNumber << "\n";

                nextAccountNumber++;

                break;
            }

            case 2: {

                if (accounts.empty()) {
                    cout << "No accounts registered yet!\n";
                    break;
                }

                cout << "\n----- ALL BANK ACCOUNTS -----\n";

                for (int i = 0; i < accounts.size(); i++) {
                    accounts[i].displayDetails();
                }

                break;
            }

            case 3: {

                cout << "Enter account number: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index == -1) {
                    cout << "Account not found!\n";
                }
                else {
                    accounts[index].displayDetails();
                }

                break;
            }

            case 4: {

                cout << "Enter account number: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index == -1) {
                    cout << "Account not found!\n";
                    break;
                }

                cout << "Enter deposit amount: ";
                cin >> amount;

                accounts[index].deposit(amount);

                break;
            }

            case 5: {

                cout << "Enter account number: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index == -1) {
                    cout << "Account not found!\n";
                    break;
                }

                cout << "Enter withdrawal amount: ";
                cin >> amount;

                accounts[index].withdraw(amount);

                break;
            }

            case 6: {
                
                cout << "Enter account number: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index == -1) {
                    cout << "Account not found!\n";
                    break;
                }

                cout << "Enter new account holder name: ";
                getline(cin >> ws, name);

                accounts[index].updateName(name);

                break;
            }

            case 7: {

                cout << "Enter account number to close: ";
                cin >> accNo;

                closeAccount(accounts, accNo);

                break;
            }

            case 8: {

                cout << "Enter account number: ";
                cin >> accNo;

                int index = findAccount(accounts, accNo);

                if (index == -1) {
                    cout << "Account not found!\n";
                    break;
                }

                accounts[index].displayTransactionHistory();

                break;
            }

            case 9:
                cout << "Thank you for using BankSphere!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}