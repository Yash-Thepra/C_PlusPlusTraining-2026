#pragma once

#include <string>

#include "constant.h"
#include "Transaction.h"

class Account
{
private:
    std::string accountNumber;
    std::string ownerId;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;

public:
    Account(std::string accountNumber, std::string ownerId, double initialBalance);

    bool deposit(double amount);

    bool withdraw(double amount);

    std::string getAccountNumber() const;

    std::string getOwnerId() const;

    double getBalance() const;

    void showMiniStatement() const;

    void showFullStatement() const;
};
