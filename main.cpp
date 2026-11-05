#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SavingsAccount.h"
#include "CurrentAccount.h"

using namespace std;

int findAccount(vector<unique_ptr<Account>>& accounts, int accNo) {

    for (int i = 0; i < accounts.size(); i++) {

        if (accounts[i]->getAccountNumber() == accNo) {
            return i;
        }
    }

    return -1;
}

void closeAccount(vector<unique_ptr<Account>>& accounts, int accNo) {

    int index = findAccount(accounts, accNo);

    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    if (accounts[index]->getBalance() != 0) {
        cout << "Account must have zero balance before closing!\n";
        return;
    }

    accounts.erase(accounts.begin() + index);

    cout << "Account closed successfully!\n";
}

int main() {

    vector<unique_ptr<Account>> accounts;

    int nextAccountNumber = 100001;
    int choice, accNo, accountType;
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

                cout << "\nSelect Account Type:\n";
                cout << "1. Savings Account\n";
                cout << "2. Current Account\n";
                cout << "Enter choice: ";
                cin >> accountType;

                if (accountType != 1 && accountType != 2) {
                    cout << "Invalid account type!\n";
                    break;
                }

                cout << "Enter account holder name: ";
                getline(cin >> ws, name);

                cout << "Enter initial balance: ";
                cin >> amount;

                if (amount < 0) {
                    cout << "Invalid initial balance!\n";
                    break;
                }

                if (accountType == 1) {

                    accounts.push_back(
                        make_unique<SavingsAccount>(
                            nextAccountNumber, name, amount
                        )
                    );

                    cout << "Savings Account created successfully!\n";
                }
                else {

                    accounts.push_back(
                        make_unique<CurrentAccount>(
                            nextAccountNumber, name, amount
                        )
                    );

                    cout << "Current Account created successfully!\n";
                }

                cout << "Account Number: " << nextAccountNumber << "\n";

                nextAccountNumber++;

                break;
            }

            case 2: {

                if (accounts.empty()) {
                    cout << "No accounts registered yet!\n";
                    break;
                }

                for (auto& acc : accounts) {
                    acc->displayDetails();
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
                    accounts[index]->displayDetails();
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

                accounts[index]->deposit(amount);

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

                accounts[index]->withdraw(amount);

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

                accounts[index]->updateName(name);

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

                accounts[index]->displayTransactionHistory();

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
