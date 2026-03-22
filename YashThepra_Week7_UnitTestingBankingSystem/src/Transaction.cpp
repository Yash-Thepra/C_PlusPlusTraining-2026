#include "Transaction.h"

Transaction::Transaction() : transactionId(""), referenceId(""), type(""), amount(0.0), balanceAfter(0.0)
{
}

Transaction::Transaction(std::string transactionId, std::string referenceId, std::string type, double amount, double balanceAfter) : transactionId(transactionId), referenceId(referenceId), type(type), amount(amount), balanceAfter(balanceAfter)
{
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

double Transaction::getBalanceAfter() const 
{ 
    return balanceAfter; 
}
