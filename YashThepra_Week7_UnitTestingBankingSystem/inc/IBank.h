#pragma once
#include <string>

class Account;
class IUser;

class IBank
{
public:
    virtual ~IBank() {}
    virtual void addUser(IUser *user) = 0;
    virtual void deleteUser(std::string userId) = 0;
    virtual IUser *login(std::string identifier, std::string password) = 0;
    virtual Account *createAccount(std::string ownerId, double initialBalance) = 0;
    virtual Account *getAccountByOwner(std::string ownerId) = 0;
    virtual Account *findAccount(std::string accountNumber) = 0;
    virtual void showAllUsers() const = 0;
    virtual void showAllAccounts() const = 0;
};
