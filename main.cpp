#include<iostream>
#include<string>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    long long balance;

public:
    Account(int accountNumber, string accountHolder, long long balance) {
        this->accountNumber=accountNumber;
        this->accountHolder=accountHolder;
        this->balance=balance;
    }

    void deposit(long long amount) {
        if(amount <= 0) {
            cout << "Invalid deposit amount!!\n";
            return;
        }
        balance+=amount;
        cout << amount << "rs deposited successfully!\n";
    }

    void withdraw(long long amount) {
        if(amount <= 0) {
            cout << "Invalid withdrawal amount!!\n";
            return;
        } else if (amount > balance) {
            cout << "Insufficient balance!!\n";
            return;
        }
        balance-=amount;
        cout << amount << "rs withdrawn successfully!\n";
    }

    void checkBalance() {
        cout << "Current Balance: Rs." << balance << "\n";
    }

    void displayDetails() {
        cout << "\n----- ACCOUNT DETAILS -----\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Account Holder : " << accountHolder << "\n";
        cout << "Balance        : Rs. " << balance << "\n";
    }
};

int main() {
    Account acc1(10001,"Aditya",10000);

    acc1.displayDetails();

    acc1.deposit(5000);
    acc1.checkBalance();

    acc1.withdraw(2000);
    acc1.checkBalance();

    return 0;
}