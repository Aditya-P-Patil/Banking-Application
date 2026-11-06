
#include "Customer.h"

Customer::Customer(string username, string password, int accountNumber)
    : User(username, password) {

    this->accountNumber = accountNumber;
}

string Customer::getRole() const {

    return "Customer";
}

int Customer::getAccountNumber() const {
    return accountNumber;
}