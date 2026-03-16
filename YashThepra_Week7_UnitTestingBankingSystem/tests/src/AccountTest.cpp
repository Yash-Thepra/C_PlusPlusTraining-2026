#include <gtest/gtest.h>

#include "Account.h"

class AccountTest : public ::testing::Test
{
protected:
    Account *account;

    void SetUp() override
    {
        account = new Account("ACC1", "U9876543210", 500.0);
    }

    void TearDown() override
    {
        delete account;
    }
};

TEST_F(AccountTest, InitialBalanceIsCorrect)
{
    EXPECT_DOUBLE_EQ(account->getBalance(), 500.0);
}

TEST_F(AccountTest, AccountNumberIsCorrect)
{
    EXPECT_EQ(account->getAccountNumber(), "ACC1");
}

TEST_F(AccountTest, OwnerIdIsCorrect)
{
    EXPECT_EQ(account->getOwnerId(), "U9876543210");
}

TEST_F(AccountTest, InitialTransactionCountIsZero)
{
    EXPECT_EQ(account->getTransactionCount(), 0);
}

class AccountDepositValidTest : public ::testing::TestWithParam<double>
{
protected:
    Account *account;
    void SetUp() override   { account = new Account("ACC1", "U9876543210", 500.0); }
    void TearDown() override { delete account; }
};

TEST_P(AccountDepositValidTest, ValidDepositReturnsTrue)
{
    EXPECT_TRUE(account->deposit(GetParam()));
}

TEST_P(AccountDepositValidTest, ValidDepositIncreasesBalance)
{
    double before = account->getBalance();
    account->deposit(GetParam());
    EXPECT_DOUBLE_EQ(account->getBalance(), before + GetParam());
}

TEST_P(AccountDepositValidTest, ValidDepositRecordsTransaction)
{
    account->deposit(GetParam());
    EXPECT_EQ(account->getTransactionCount(), 1);
}

TEST_P(AccountDepositValidTest, ValidDepositTransactionTypeIsDeposit)
{
    account->deposit(GetParam());
    EXPECT_EQ(account->getTransactions()[0].getType(), "DEPOSIT");
}

TEST_P(AccountDepositValidTest, ValidDepositTransactionAmountIsCorrect)
{
    account->deposit(GetParam());
    EXPECT_DOUBLE_EQ(account->getTransactions()[0].getAmount(), GetParam());
}

TEST_P(AccountDepositValidTest, ValidDepositTransactionBalanceAfterIsCorrect)
{
    double before = account->getBalance();
    account->deposit(GetParam());
    EXPECT_DOUBLE_EQ(account->getTransactions()[0].getBalanceAfter(), before + GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    ValidDepositAmounts,
    AccountDepositValidTest,
    ::testing::Values(0.01, 1.0, 100.0, 500.0, 9999.99)
);

class AccountDepositInvalidTest : public ::testing::TestWithParam<double>
{
protected:
    Account *account;
    void SetUp() override   
    { 
        account = new Account("ACC1", "U9876543210", 500.0);
    }

    void TearDown() override 
    { 
        delete account; 
    }
};

TEST_P(AccountDepositInvalidTest, InvalidDepositReturnsFalse)
{
    EXPECT_FALSE(account->deposit(GetParam()));
}

TEST_P(AccountDepositInvalidTest, InvalidDepositDoesNotChangeBalance)
{
    account->deposit(GetParam());
    EXPECT_DOUBLE_EQ(account->getBalance(), 500.0);
}

TEST_P(AccountDepositInvalidTest, InvalidDepositDoesNotRecordTransaction)
{
    account->deposit(GetParam());
    EXPECT_EQ(account->getTransactionCount(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    InvalidDepositAmounts,
    AccountDepositInvalidTest,
    ::testing::Values(0.0, -0.01, -1.0, -100.0)
);

class AccountWithdrawValidTest : public ::testing::TestWithParam<double>
{
protected:
    Account *account;
    void SetUp() override   { account = new Account("ACC1", "U9876543210", 1000.0); }
    void TearDown() override { delete account; }
};

TEST_P(AccountWithdrawValidTest, ValidWithdrawReturnsTrue)
{
    EXPECT_TRUE(account->withdraw(GetParam()));
}

TEST_P(AccountWithdrawValidTest, ValidWithdrawDecreasesBalance)
{
    double before = account->getBalance();
    account->withdraw(GetParam());
    EXPECT_DOUBLE_EQ(account->getBalance(), before - GetParam());
}

TEST_P(AccountWithdrawValidTest, ValidWithdrawRecordsTransaction)
{
    account->withdraw(GetParam());
    EXPECT_EQ(account->getTransactionCount(), 1);
}

TEST_P(AccountWithdrawValidTest, ValidWithdrawTransactionTypeIsWithdraw)
{
    account->withdraw(GetParam());
    EXPECT_EQ(account->getTransactions()[0].getType(), "WITHDRAW");
}

TEST_P(AccountWithdrawValidTest, ValidWithdrawTransactionAmountIsCorrect)
{
    account->withdraw(GetParam());
    EXPECT_DOUBLE_EQ(account->getTransactions()[0].getAmount(), GetParam());
}

TEST_P(AccountWithdrawValidTest, ValidWithdrawTransactionBalanceAfterIsCorrect)
{
    double before = account->getBalance();
    account->withdraw(GetParam());
    EXPECT_DOUBLE_EQ(account->getTransactions()[0].getBalanceAfter(), before - GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    ValidWithdrawAmounts,
    AccountWithdrawValidTest,
    ::testing::Values(0.01, 1.0, 100.0, 499.99, 500.0)
);

class AccountWithdrawInvalidTest : public ::testing::TestWithParam<double>
{
protected:
    Account *account;
    void SetUp() override   { account = new Account("ACC1", "U9876543210", 500.0); }
    void TearDown() override { delete account; }
};

TEST_P(AccountWithdrawInvalidTest, InvalidWithdrawReturnsFalse)
{
    EXPECT_FALSE(account->withdraw(GetParam()));
}

TEST_P(AccountWithdrawInvalidTest, InvalidWithdrawDoesNotChangeBalance)
{
    account->withdraw(GetParam());
    EXPECT_DOUBLE_EQ(account->getBalance(), 500.0);
}

TEST_P(AccountWithdrawInvalidTest, InvalidWithdrawDoesNotRecordTransaction)
{
    account->withdraw(GetParam());
    EXPECT_EQ(account->getTransactionCount(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    InvalidWithdrawAmounts,
    AccountWithdrawInvalidTest,
    ::testing::Values(0.0, -0.01, -1.0, 0.01, 100.0, 9999.99)
);

TEST_F(AccountTest, MultipleDepositsAccumulateCorrectly)
{
    account->deposit(100.0);
    account->deposit(200.0);
    EXPECT_DOUBLE_EQ(account->getBalance(), 800.0);
}

TEST_F(AccountTest, TransactionCountIncreasesWithEachValidOperation)
{
    account->deposit(100.0);
    account->deposit(200.0);
    EXPECT_EQ(account->getTransactionCount(), 2);
}

TEST_F(AccountTest, WithdrawAfterDepositSucceeds)
{
    account->deposit(500.0);    
    EXPECT_TRUE(account->withdraw(400.0)); 
}

TEST_F(AccountTest, TransactionsAreRecordedInOrder)
{
    account->deposit(100.0);
    account->deposit(200.0);
    EXPECT_EQ(account->getTransactions()[0].getType(), "DEPOSIT");
    EXPECT_DOUBLE_EQ(account->getTransactions()[0].getAmount(), 100.0);
    EXPECT_EQ(account->getTransactions()[1].getType(), "DEPOSIT");
    EXPECT_DOUBLE_EQ(account->getTransactions()[1].getAmount(), 200.0);
}

TEST_F(AccountTest, TransactionIdsAreSequential)
{
    account->deposit(50.0);
    account->deposit(50.0);
    EXPECT_EQ(account->getTransactions()[0].getTransactionId(), "T1");
    EXPECT_EQ(account->getTransactions()[1].getTransactionId(), "T2");
}

TEST_F(AccountTest, ReferenceIdsAreSequential)
{
    account->deposit(50.0);
    account->deposit(50.0);
    EXPECT_EQ(account->getTransactions()[0].getReferenceId(), "REF1");
    EXPECT_EQ(account->getTransactions()[1].getReferenceId(), "REF2");
}

TEST_F(AccountTest, FailedDepositDoesNotIncrementTransactionId)
{
    account->deposit(-10.0);  
    account->deposit(100.0);  
    EXPECT_EQ(account->getTransactions()[0].getTransactionId(), "T1");
}

TEST_F(AccountTest, MixedOperationsProduceCorrectTransactionCount)
{
    account->deposit(200.0);
    account->deposit(300.0);   
    account->withdraw(400.0);  
    EXPECT_EQ(account->getTransactionCount(), 3);
}

TEST_F(AccountTest, BalanceAfterWithdrawIsCorrect)
{
    account->deposit(500.0);  
    account->withdraw(300.0); 
    EXPECT_DOUBLE_EQ(account->getBalance(), 700.0);
}
