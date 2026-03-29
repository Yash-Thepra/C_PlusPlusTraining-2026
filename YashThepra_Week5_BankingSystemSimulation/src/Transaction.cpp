#include "Transaction.h"

Transaction::Transaction()
{
    transactionId = "";
    referenceId = "";
    type = "";
    amount = 0.0;
}

Transaction::Transaction(std::string transactionID, std::string referenceId, std::string type, double amount)
{
    this->transactionId = transactionID;
    this->referenceId = referenceId;
    this->type = type;
    this->amount = amount;
}

std::string Transaction::getTransactionId() const
{
    return transactionId;
}

std::string Transaction::getReferenceId() const
{
    return referenceId;
}

std::string Transaction::getType() const
{
    return type;
}

double Transaction::getAmount() const
{
    return amount;
}
