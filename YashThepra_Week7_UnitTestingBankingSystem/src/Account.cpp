#include <iostream>

#include "Account.h"

Account::Account(std::string accountNumber, std::string ownerId, double initialBalance) : accountNumber(accountNumber), ownerId(ownerId), balance(initialBalance), transactionCount(0)
{
}

bool Account::deposit(double amount)
{
    if (amount <= 0 || transactionCount >= MAX_TRANSACTIONS)
    {
        return false;
    }
    balance += amount;
    std::string tId = "T" + std::to_string(transactionCount + 1);
    std::string ref = "REF" + std::to_string(transactionCount + 1);
    transactions[transactionCount++] = Transaction(tId, ref, "DEPOSIT", amount, balance);
    return true;
}

bool Account::withdraw(double amount)
{
    if (amount <= 0 || amount > balance - MIN_OPENING_BALANCE || transactionCount >= MAX_TRANSACTIONS)
    {
        return false;
    }
    balance -= amount;
    std::string tId = "T" + std::to_string(transactionCount + 1);
    std::string ref = "REF" + std::to_string(transactionCount + 1);
    transactions[transactionCount++] = Transaction(tId, ref, "WITHDRAW", amount, balance);
    return true;
}

std::string Account::getAccountNumber() const 
{ 
    return accountNumber; 
}

std::string Account::getOwnerId() const 
{ 
    return ownerId; 
}

double Account::getBalance() const 
{ 
    return balance; 
}

int Account::getTransactionCount() const 
{ 
    return transactionCount; 
}

const Transaction *Account::getTransactions() const
{
    return transactions;
}

void Account::showMiniStatement() const
{
    int start = transactionCount - 5;
    if (start < 0)
    {
        start = 0;
    }
    for (int i = start; i < transactionCount; i++)
    {
        std::cout << transactions[i].getTransactionId() << " | " << transactions[i].getReferenceId() << " | " << transactions[i].getType() << " | " << transactions[i].getAmount() << "\n";
    }
}

void Account::showFullStatement() const
{
    for (int i = 0; i < transactionCount; i++)
    {
        std::cout << transactions[i].getTransactionId() << " | "<< transactions[i].getReferenceId() << " | " << transactions[i].getType() << " | " << transactions[i].getAmount() << "\n";
    }
}
