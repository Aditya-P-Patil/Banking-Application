
#include <iostream>
#include <string>

#include "Bank.h"

using namespace std;

void adminMenu(Bank& bank) {

    int choice, accNo;
    long long amount;
    string name;

    while (true) {

        cout << "\n========== ADMIN DASHBOARD ==========\n";
        cout << "1. Display All Accounts\n";
        cout << "2. Search Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Update Account Details\n";
        cout << "6. Close Account\n";
        cout << "7. Transfer Money\n";
        cout << "8. View Transaction Summary\n";
        cout << "9. Logout\n";
        cout << "=====================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                bank.displayAllAccounts();
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> accNo;
                bank.searchAccount(accNo);
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter amount: ";
                cin >> amount;

                bank.depositMoney(accNo, amount);
                break;

            case 4:
                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter amount: ";
                cin >> amount;

                bank.withdrawMoney(accNo, amount);
                break;

            case 5:
                cout << "Enter account number: ";
                cin >> accNo;

                cout << "Enter new name: ";
                getline(cin >> ws, name);

                bank.updateAccount(accNo, name);
                break;

            case 6:
                cout << "Enter account number: ";
                cin >> accNo;

                bank.closeAccount(accNo);
                break;

            case 7: {
                int fromAccNo, toAccNo;
                long long amount;

                cout << "Enter Sender Account Number: ";
                cin >> fromAccNo;

                cout << "Enter Receiver Account Number: ";
                cin >> toAccNo;

                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                bank.transferMoney(fromAccNo, toAccNo, amount);
                break;
            }

            case 8: {
                int accNo;

                cout << "Enter Account Number: ";
                cin >> accNo;

                bank.showTransactionSummary(accNo);
                break;
            }

            case 9:
                cout << "Admin logged out successfully!\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
}


void customerMenu(Bank& bank, int accNo) {

    int choice;
    long long amount;

    while (true) {

        cout << "\n========== CUSTOMER DASHBOARD ==========\n";
        cout << "1. View Account Details\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Transaction History\n";
        cout << "6. Transfer Money\n";
        cout << "7. View Transaction Summary\n";
        cout << "8. Logout\n";
        cout << "========================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                bank.searchAccount(accNo);
                break;

            case 2:
                bank.checkBalance(accNo);
                break;

            case 3:
                cout << "Enter deposit amount: ";
                cin >> amount;

                bank.depositMoney(accNo, amount);
                break;

            case 4:
                cout << "Enter withdrawal amount: ";
                cin >> amount;

                bank.withdrawMoney(accNo, amount);
                break;

            case 5:
                bank.showTransactionHistory(accNo);
                break;

            case 6: {
                int toAccNo;
                long long amount;

                cout << "Enter Receiver Account Number: ";
                cin >> toAccNo;

                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                bank.transferMoney(accNo, toAccNo, amount);
                break;
            }

            case 7:
                bank.showTransactionSummary(accNo);
                break;

            case 8:
                cout << "Customer logged out successfully!\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
}


int main() {

    Bank bank;

    int choice, accountType;
    long long amount;

    string name, username, password;

    while (true) {

        cout << "\n========== BANKSPHERE ==========\n";
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Create New Account\n";
        cout << "4. Exit\n";
        cout << "================================\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1: {

                cout << "Enter admin username: ";
                cin >> username;

                cout << "Enter admin password: ";
                cin >> password;

                User* user = bank.authenticateUser(username, password);

                if (user != nullptr && user->getRole() == "Admin") {

                    cout << "\nAdmin login successful!\n";

                    adminMenu(bank);
                }
                else {
                    cout << "Invalid admin credentials!\n";
                }

                break;
            }

            case 2: {

                cout << "Enter username: ";
                cin >> username;

                cout << "Enter password: ";
                cin >> password;

                User* user = bank.authenticateUser(username, password);

                if (user != nullptr && user->getRole() == "Customer") {

                    Customer* customer = dynamic_cast<Customer*>(user);

                    cout << "\nCustomer login successful!\n";
                    cout << "Welcome, " << customer->getUsername() << "!\n";

                    customerMenu(bank, customer->getAccountNumber());
                }
                else {
                    cout << "Invalid customer credentials!\n";
                }

                break;
            }

            case 3: {

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

                cout << "Choose username: ";
                cin >> username;

                cout << "Choose password: ";
                cin >> password;

                cout << "Enter initial balance: ";
                cin >> amount;

                if (accountType == 1) {
                    bank.createSavingsAccount(
                        name, amount, username, password
                    );
                }
                else {
                    bank.createCurrentAccount(
                        name, amount, username, password
                    );
                }

                break;
            }

            case 4:
                cout << "Thank you for using BankSphere!\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
