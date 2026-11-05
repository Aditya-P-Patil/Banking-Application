
#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(
    int accNo,
    string name,
    long long initialBalance
) : Account(accNo, name, initialBalance) {

    interestRate = 4.0;
}

double SavingsAccount::calculateInterest() {

    return balance * interestRate / 100.0;
}

void SavingsAccount::withdraw(long long amount) {

    if (amount <= 0) {
        cout << "Invalid withdrawal amount!\n";
        transactions.push_back({"Withdrawal", amount, "FAILED"});
        return;
    }

    if (balance - amount < minimumBalance) {
        cout << "Minimum balance of Rs. "
             << minimumBalance << " must be maintained!\n";

        transactions.push_back({"Withdrawal", amount, "FAILED"});
        return;
    }

    balance -= amount;

    transactions.push_back({"Withdrawal", amount, "SUCCESS"});

    cout << "Amount withdrawn successfully!\n";
}

void SavingsAccount::displayDetails() {

    Account::displayDetails();

    cout << "Account Type   : Savings Account\n";
    cout << "Interest Rate  : " << interestRate << "%\n";
    cout << "Interest       : Rs. " << calculateInterest() << "\n";
}
