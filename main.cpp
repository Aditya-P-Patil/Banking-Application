#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    long long balance;

public:
    Account(int accNo, string name, long long initialBalance) {
        accountNumber = accNo;
        accountHolder = name;
        balance = initialBalance;
    }

    void deposit(long long amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount!\n";
            return;
        }

        balance += amount;
        cout << "Amount deposited successfully!\n";
    }

    void withdraw(long long amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;
        cout << "Amount withdrawn successfully!\n";
    }

    void checkBalance() {
        cout << "Current Balance: Rs. " << balance << "\n";
    }

    void displayDetails() {
        cout << "\n----- ACCOUNT DETAILS -----\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Account Holder : " << accountHolder << "\n";
        cout << "Balance        : Rs. " << balance << "\n";
    }

    int getAccountNumber() {
        return accountNumber;
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


int main() {

    vector<Account> accounts;

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
        cout << "6. Exit\n";
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

            case 6:
                cout << "Thank you for using BankSphere!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}