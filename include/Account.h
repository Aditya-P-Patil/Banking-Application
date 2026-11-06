
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class Account {

protected:
    int accountNumber;
    string accountHolder;
    long long balance;

    vector<Transaction> transactions;

public:

    Account(int accNo, string name, long long initialBalance);

    virtual ~Account() = default;

    int getAccountNumber();
    long long getBalance();

    void updateName(string newName);

    void deposit(long long amount);

    virtual void withdraw(long long amount);

    void checkBalance();

    virtual void displayDetails();

    void displayTransactionHistory();

    int getLastTransactionId();

    void updateLastTransaction(
        string type,
        string status,
        int relatedAccount,
        int transactionId
    );

    void displayTransactionSummary();

    string getAccountHolder();

    virtual double calculateInterest() = 0;
    
    virtual string getAccountType() = 0;

    const vector<Transaction>& getTransactions() const;
    void addTransaction(const Transaction& txn);
};
