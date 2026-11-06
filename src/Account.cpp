#include "Account.h"
#include <iomanip>

Account::Account(int accNo, string name, long long initialBalance) {

    accountNumber = accNo;
    accountHolder = name;
    balance = initialBalance;
}

int Account::getAccountNumber() {
    return accountNumber;
}

long long Account::getBalance() {
    return balance;
}

void Account::updateName(string newName) {

    if (newName.empty()) {
        cout << "Name cannot be empty!\n";
        return;
    }

    accountHolder = newName;

    cout << "Name updated successfully!\n";
}

void Account::deposit(long long amount) {

    if (amount <= 0) {
        cout << "Invalid deposit amount!\n";
        transactions.push_back({"Deposit", amount, "FAILED"});
        return;
    }

    balance += amount;

    transactions.push_back({"Deposit", amount, "SUCCESS"});

    cout << "Amount deposited successfully!\n";
}

void Account::withdraw(long long amount) {

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

void Account::checkBalance() {

    cout << "Current Balance: Rs. " << balance << "\n";
}

void Account::displayDetails() {

    cout << "\n----- ACCOUNT DETAILS -----\n";

    cout << "Account Number : " << accountNumber << "\n";
    cout << "Account Holder : " << accountHolder << "\n";
    cout << "Balance        : Rs. " << balance << "\n";
}

void Account::displayTransactionHistory() {

    if (transactions.empty()) {
        cout << "No transactions available!\n";
        return;
    }

    cout << "\n========== TRANSACTION HISTORY ==========\n";

    for (int i = 0; i < transactions.size(); i++) {

        cout << "\nTransaction ID : "
             << transactions[i].transactionId << "\n";

        cout << "Date & Time     : "
             << put_time(localtime(&transactions[i].timestamp),"%d-%m-%Y %I:%M:%S %p") << "\n";

        cout << "Type            : "
             << transactions[i].type << "\n";

        cout << "Amount          : Rs. "
             << transactions[i].amount << "\n";

        cout << "Status          : "
             << transactions[i].status << "\n";

        if (transactions[i].relatedAccount != -1) {
            cout << "Related Account : "
                 << transactions[i].relatedAccount << "\n";
        }

        cout << "-----------------------------------------\n";
    }

    cout << "=========================================\n";
}

int Account::getLastTransactionId() {

    if (transactions.empty()) {
        return -1;
    }

    return transactions.back().transactionId;
}


void Account::updateLastTransaction(
    string type,
    string status,
    int relatedAccount,
    int transactionId
) {

    if (transactions.empty()) {
        return;
    }

    Transaction& txn = transactions.back();

    txn.type = type;
    txn.status = status;
    txn.relatedAccount = relatedAccount;
    txn.transactionId = transactionId;
}

void Account::displayTransactionSummary() {

    long long deposits = 0;
    long long withdrawals = 0;
    long long transfersSent = 0;
    long long transfersReceived = 0;

    int totalTransactions = transactions.size();
    int failedTransactions = 0;

    for (auto& txn : transactions) {

        if (txn.status == "FAILED") {
            failedTransactions++;
            continue;
        }

        if (txn.type == "Deposit") {
            deposits += txn.amount;
        }
        else if (txn.type == "Withdrawal") {
            withdrawals += txn.amount;
        }
        else if (txn.type == "Transfer Sent") {
            transfersSent += txn.amount;
        }
        else if (txn.type == "Transfer Received") {
            transfersReceived += txn.amount;
        }
    }

    cout << "\n========== TRANSACTION SUMMARY ==========\n";

    cout << "Total Deposits       : Rs. " << deposits << "\n";
    cout << "Total Withdrawals    : Rs. " << withdrawals << "\n";
    cout << "Transfers Sent       : Rs. " << transfersSent << "\n";
    cout << "Transfers Received   : Rs. " << transfersReceived << "\n";

    cout << "Total Transactions   : " << totalTransactions << "\n";
    cout << "Failed Transactions  : " << failedTransactions << "\n";

    cout << "=========================================\n";
}

string Account::getAccountHolder() {
    return accountHolder;
}

const vector<Transaction>& Account::getTransactions() const {
    return transactions;
}

void Account::addTransaction(const Transaction& txn) {
    transactions.push_back(txn);
}