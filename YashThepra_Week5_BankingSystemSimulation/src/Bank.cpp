#include <iostream>

#include "Bank.h"

Bank *Bank::instance = nullptr;

Bank::Bank()
{
    userCount = 0;
    accountCount = 0;
}

Bank::~Bank()
{
    for (int i = 0; i < userCount; i++)
    {
        delete users[i];
    }
    for (int i = 0; i < accountCount; i++)
    {
        delete accounts[i];
    }
}

Bank &Bank::getInstance()
{
    if (!instance)
    {
        instance = new Bank();
    }
    return *instance;
}

void Bank::addUser(IUser *user)
{
    if (userCount < MAX_USERS)
    {
        users[userCount++] = user;
    }
}

void Bank::deleteUser(std::string userId)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getId() == userId)
        {
            delete users[i];
            for (int j = i; j < userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            userCount--;
            break;
        }
    }
}

IUser *Bank::login(std::string identifier, std::string password)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i]->getMobile() == identifier && users[i]->authenticate(password))
        {
            return users[i];
        }
    }
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i]->getAccountNumber() == identifier)
        {
            std::string owner = accounts[i]->getOwnerId();
            for (int j = 0; j < userCount; j++)
            {
                if (users[j]->getId() == owner && users[j]->authenticate(password))
                {
                    return users[j];
                }
            }
        }
    }

    return nullptr;
}

Account *Bank::createAccount(std::string ownerId, double initialBalance)
{
    Account *account = nullptr;
    if (accountCount < MAX_ACCOUNTS)
    {
        std::string accountNumber = "ACC" + std::to_string(accountCount + 1);
        account = new Account(accountNumber, ownerId, initialBalance);
        accounts[accountCount++] = account;
    }
    return account;
}

Account *Bank::getAccountByOwner(std::string ownerId)
{
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i]->getOwnerId() == ownerId)
        {
            return accounts[i];
        }
    }
    return nullptr;
}

Account *Bank::findAccount(std::string accountNumber)
{
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i]->getAccountNumber() == accountNumber)
        {
            return accounts[i];
        }
    }
    return nullptr;
}

void Bank::showAllUsers() const
{
    for (int i = 0; i < userCount; i++)
    {
        std::cout << users[i]->getId() << " | " << users[i]->getName() << "\n";
    }
}

void Bank::showAllAccounts() const
{
    for (int i = 0; i < accountCount; i++)
    {
        std::cout << accounts[i]->getAccountNumber() << " | " << accounts[i]->getBalance() << "\n";
    }
}
