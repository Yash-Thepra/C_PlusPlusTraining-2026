#pragma once

#include <string>

class Transaction
{
private:
    std::string transactionId;
    std::string referenceId;
    std::string type;
    double amount;
    double balanceAfter;

public:
    Transaction();

    Transaction(std::string transactionId, std::string referenceId,std::string type, double amount, double balance);

    std::string getTransactionId() const;

    std::string getReferenceId() const;

    std::string getType() const;

    double getAmount() const;

    double getBalanceAfter() const;
};
