#pragma once

#include "Account.h"
#include "constant.h"
#include "IUser.h"

class Bank
{
private:
    static Bank *instance;
    IUser *users[MAX_USERS];
    int userCount;
    Account *accounts[MAX_ACCOUNTS];
    int accountCount;

    Bank();

public:
    ~Bank();
    static Bank &getInstance();

    void addUser(IUser *user);

    void deleteUser(std::string userId);

    IUser *login(std::string identifier, std::string password);

    Account *createAccount(std::string ownerId, double initialBalance);

    Account *getAccountByOwner(std::string ownerId);

    Account *findAccount(std::string accountNumber);

    void showAllUsers() const;

    void showAllAccounts() const;
};
