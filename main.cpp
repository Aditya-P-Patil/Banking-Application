#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

int main() {

    Bank bank;

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
        cout << "8. Check Balance\n";
        cout << "9. Transaction History\n";
        cout << "10. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {

                cout << "\n1. Savings Account\n";
                cout << "2. Current Account\n";
                cout << "Select account type: ";
                cin >> accountType;

                if (accountType != 1 && accountType != 2) {
                    cout << "Invalid account type!\n";
                    break;
                }

                cout << "Enter account holder name: ";
                getline(cin >> ws, name);

                cout << "Enter initial balance: ";
                cin >> amount;

                if (accountType == 1) {
                    bank.createSavingsAccount(name, amount);
                }
                else {
                    bank.createCurrentAccount(name, amount);
                }

                break;
            }

            case 2:

                bank.displayAllAccounts();
                break;

            case 3:

                cout << "Enter account number: ";
                cin >> accNo;

                bank.searchAccount(accNo);
                break;

            case 4:

                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter deposit amount: ";
                cin >> amount;

                bank.depositMoney(accNo, amount);
                break;

            case 5:

                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter withdrawal amount: ";
                cin >> amount;

                bank.withdrawMoney(accNo, amount);
                break;

            case 6:

                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter new account holder name: ";
                getline(cin >> ws, name);

                bank.updateAccount(accNo, name);
                break;

            case 7:

                cout << "Enter account number to close: ";
                cin >> accNo;

                bank.closeAccount(accNo);
                break;

            case 8:

                cout << "Enter account number: ";
                cin >> accNo;

                bank.checkBalance(accNo);
                break;

            case 9:

                cout << "Enter account number: ";
                cin >> accNo;

                bank.showTransactionHistory(accNo);
                break;

            case 10:

                cout << "Thank you for using BankSphere!\n";
                return 0;

            default:

                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
