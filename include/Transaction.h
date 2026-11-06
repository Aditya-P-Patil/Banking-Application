#pragma once

#include <string>
#include <ctime>
using namespace std;

struct Transaction {

    inline static int nextTransactionId = 1001;

    int transactionId;
    string type;
    long long amount;
    string status;
    int relatedAccount;
    time_t timestamp;

    // Constructor for new transactions
    Transaction(
        string type,
        long long amount,
        string status,
        int relatedAccount = -1
    ) {
        transactionId = nextTransactionId++;
        this->type = type;
        this->amount = amount;
        this->status = status;
        this->relatedAccount = relatedAccount;

        timestamp = time(nullptr);
    }

    // Constructor for restoring existing transactions
    Transaction(
        int id,
        string type,
        long long amount,
        string status,
        int relatedAccount,
        time_t timestamp
    ) {
        transactionId = id;
        this->type = type;
        this->amount = amount;
        this->status = status;
        this->relatedAccount = relatedAccount;
        this->timestamp = timestamp;

        // Prevent future ID duplication
        if (id >= nextTransactionId) {
            nextTransactionId = id + 1;
        }
    }
};