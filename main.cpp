#include <iostream>
#include <string>
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
};

int main() {

    Account acc1(100001, "Aditya", 10000);

    int choice;
    long long amount;

    while (true) {
        cout << "\n========== BANKSPHERE ==========\n";
        cout << "1. Account Details\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                acc1.displayDetails();
                break;

            case 2:
                acc1.checkBalance();
                break;

            case 3:
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc1.deposit(amount);
                break;

            case 4:
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc1.withdraw(amount);
                break;

            case 5:
                cout << "Thank you for using BankSphere!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
