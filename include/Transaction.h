#pragma once

#include <string>
using namespace std;

struct Transaction {

    inline static int nextTransactionId = 1001;

    int transactionId;
    string type;
    long long amount;
    string status;
    int relatedAccount;

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
    }
};