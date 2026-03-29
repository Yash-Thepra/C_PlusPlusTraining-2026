#pragma once

#include <string>

class Transaction
{
private:
    std::string transactionId;
    std::string referenceId;
    std::string type;
    double amount;

public:
    Transaction();
    Transaction(std::string transactionId, std::string referenceID, std::string type, double amount);

    std::string getTransactionId() const;

    std::string getReferenceId() const;

    std::string getType() const;

    double getAmount() const;
};
