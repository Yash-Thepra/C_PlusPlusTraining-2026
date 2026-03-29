#include <iostream>

#include "Account.h"

Account::Account(std::string accountNumber, std::string ownerId, double initialBalance)
{
    this->accountNumber = accountNumber;
    this->ownerId = ownerId;
    this->balance = initialBalance;
    transactionCount = 0;
}

bool Account::deposit(double amount)
{
    bool check = false;
    if (amount > 0 && transactionCount < MAX_TRANSACTIONS)
    {
        check = true;
        balance += amount;
        std::string tId = "T" + std::to_string(transactionCount + 1);
        std::string ref = "REF" + std::to_string(transactionCount + 1);
        transactions[transactionCount++] = Transaction(tId, ref, "DEPOSIT", amount);
    }
    return check;
}

bool Account::withdraw(double amount)
{
    bool check = false;
    if (amount > 0 && amount <= balance - MIN_OPENING_BALANCE && transactionCount < MAX_TRANSACTIONS)
    {
        check = true;
        balance -= amount;
        std::string tId = "T" + std::to_string(transactionCount + 1);
        std::string ref = "REF" + std::to_string(transactionCount + 1);
        transactions[transactionCount++] = Transaction(tId, ref, "WITHDRAW", amount);
    }
    return check;
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
        std::cout << transactions[i].getTransactionId() << " | " << transactions[i].getReferenceId() << " | " << transactions[i].getType() << " | " << transactions[i].getAmount() << "\n";
    }
}
