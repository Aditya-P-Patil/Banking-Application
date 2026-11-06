
#include "CurrentAccount.h"

CurrentAccount::CurrentAccount(
    int accNo,
    string name,
    long long initialBalance
) : Account(accNo, name, initialBalance) {
}

double CurrentAccount::calculateInterest() {

    return 0;
}

void CurrentAccount::withdraw(long long amount) {

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

void CurrentAccount::displayDetails() {

    Account::displayDetails();

    cout << "Account Type   : Current Account\n";
    cout << "Interest       : Not Applicable\n";
}

string CurrentAccount::getAccountType() {
    return "Current";
}