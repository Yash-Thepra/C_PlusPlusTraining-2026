#pragma once

#include <gmock/gmock.h>

#include "IBank.h"

class MockBank : public IBank
{
public:
    MOCK_METHOD(void, addUser, (IUser * user), (override));
    MOCK_METHOD(void, deleteUser, (std::string userId), (override));
    MOCK_METHOD(IUser *, login, (std::string identifier, std::string password), (override));
    MOCK_METHOD(Account *, createAccount, (std::string ownerId, double initialBalance), (override));
    MOCK_METHOD(Account *, getAccountByOwner, (std::string ownerId), (override));
    MOCK_METHOD(Account *, findAccount, (std::string accountNumber), (override));
    MOCK_METHOD(void, showAllUsers, (), (const, override));
    MOCK_METHOD(void, showAllAccounts, (), (const, override));
}; 
