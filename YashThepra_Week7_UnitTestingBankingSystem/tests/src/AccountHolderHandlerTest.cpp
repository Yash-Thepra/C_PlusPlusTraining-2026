#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Account.h"
#include "AccountHolder.h"
#include "MockBank.h"

using ::testing::_;

class AccountHolderHandlerTest : public ::testing::Test
{
protected:
    testing::NiceMock<MockBank> *mockBank;
    AccountHolder *holder;
    Account *fakeAccount;

    void SetUp() override
    {
        mockBank = new testing::NiceMock<MockBank>();
        holder = new AccountHolder("U9876543210", "Riya Sharma", "9876543210", "pass1234");
        fakeAccount = new Account("ACC1", "U9876543210", 500.0);
    }

    void TearDown() override
    {
        delete holder;
        delete fakeAccount;
        delete mockBank;
    }
};

TEST_F(AccountHolderHandlerTest, OpenAccount_AlreadyExists_ReturnsFalse)
{
    ON_CALL(*mockBank, getAccountByOwner("U9876543210")).WillByDefault(testing::Return(fakeAccount));
    EXPECT_FALSE(holder->handleOpenAccount(*mockBank));
}

TEST_F(AccountHolderHandlerTest, OpenAccount_AlreadyExists_DoesNotCallCreate)
{
    ON_CALL(*mockBank, getAccountByOwner(_)).WillByDefault(testing::Return(fakeAccount));
    EXPECT_CALL(*mockBank, createAccount(_, _)).Times(0);
    holder->handleOpenAccount(*mockBank);
}

TEST_F(AccountHolderHandlerTest, OpenAccount_NoAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleOpenAccount(*mockBank);
}

TEST_F(AccountHolderHandlerTest, Deposit_NoAccount_ReturnsFalse)
{
    ON_CALL(*mockBank, getAccountByOwner(_)).WillByDefault(testing::Return(nullptr));
    EXPECT_FALSE(holder->handleDeposit(*mockBank));
}

TEST_F(AccountHolderHandlerTest, Deposit_NoAccount_CallsGetAccountByOwnerWithCorrectId)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleDeposit(*mockBank);
}

TEST_F(AccountHolderHandlerTest, Deposit_NoAccount_NeverCallsCreateAccount)
{
    ON_CALL(*mockBank, getAccountByOwner(_)).WillByDefault(testing::Return(nullptr));
    EXPECT_CALL(*mockBank, createAccount(_, _)).Times(0);
    holder->handleDeposit(*mockBank);
}

TEST_F(AccountHolderHandlerTest, Withdraw_NoAccount_ReturnsFalse)
{
    ON_CALL(*mockBank, getAccountByOwner(_)).WillByDefault(testing::Return(nullptr));
    EXPECT_FALSE(holder->handleWithdraw(*mockBank));
}

TEST_F(AccountHolderHandlerTest, Withdraw_NoAccount_CallsGetAccountByOwnerWithCorrectId)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleWithdraw(*mockBank);
}

TEST_F(AccountHolderHandlerTest, Withdraw_NoAccount_NeverCallsCreateAccount)
{
    ON_CALL(*mockBank, getAccountByOwner(_)).WillByDefault(testing::Return(nullptr));
    EXPECT_CALL(*mockBank, createAccount(_, _)).Times(0);
    holder->handleWithdraw(*mockBank);
}

TEST_F(AccountHolderHandlerTest, ViewBalance_NoAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleViewBalance(*mockBank);
}

TEST_F(AccountHolderHandlerTest, ViewBalance_WithAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(fakeAccount));
    holder->handleViewBalance(*mockBank);
}

TEST_F(AccountHolderHandlerTest, MiniStatement_NoAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleMiniStatement(*mockBank);
}

TEST_F(AccountHolderHandlerTest, MiniStatement_WithAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(fakeAccount));
    holder->handleMiniStatement(*mockBank);
}

TEST_F(AccountHolderHandlerTest, FullStatement_NoAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(nullptr));
    holder->handleFullStatement(*mockBank);
}

TEST_F(AccountHolderHandlerTest, FullStatement_WithAccount_CallsGetAccountByOwnerOnce)
{
    EXPECT_CALL(*mockBank, getAccountByOwner("U9876543210"))
        .Times(1)
        .WillOnce(testing::Return(fakeAccount));
    holder->handleFullStatement(*mockBank);
}
