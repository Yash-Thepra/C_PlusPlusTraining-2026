#include <gtest/gtest.h>

#include "Transaction.h"

class TransactionTest : public ::testing::Test
{
protected:
    Transaction *transaction;

    void SetUp() override
    {
        transaction = new Transaction("T1", "REF1", "DEPOSIT", 200.0, 700.0);
    }

    void TearDown() override
    {
        delete transaction;
    }
};

TEST_F(TransactionTest, GetTransactionIdReturnsCorrectValue)
{
    EXPECT_EQ(transaction->getTransactionId(), "T1");
}

TEST_F(TransactionTest, GetReferenceIdReturnsCorrectValue)
{
    EXPECT_EQ(transaction->getReferenceId(), "REF1");
}

TEST_F(TransactionTest, GetTypeReturnsCorrectValue)
{
    EXPECT_EQ(transaction->getType(), "DEPOSIT");
}

TEST_F(TransactionTest, GetAmountReturnsCorrectValue)
{
    EXPECT_DOUBLE_EQ(transaction->getAmount(), 200.0);
}

TEST_F(TransactionTest, GetBalanceAfterReturnsCorrectValue)
{
    EXPECT_DOUBLE_EQ(transaction->getBalanceAfter(), 700.0);
}

TEST_F(TransactionTest, DefaultConstructorSetsEmptyStrings)
{
    Transaction t;
    EXPECT_EQ(t.getTransactionId(), "");
    EXPECT_EQ(t.getReferenceId(), "");
    EXPECT_EQ(t.getType(), "");
}

TEST_F(TransactionTest, DefaultConstructorSetsZeroAmount)
{
    Transaction t;
    EXPECT_DOUBLE_EQ(t.getAmount(), 0.0);
}

TEST_F(TransactionTest, DefaultConstructorSetsZeroBalanceAfter)
{
    Transaction t;
    EXPECT_DOUBLE_EQ(t.getBalanceAfter(), 0.0);
}

struct TransactionTypeCase
{
    std::string type;
};

class TransactionTypeTest : public ::testing::TestWithParam<TransactionTypeCase>
{
};

TEST_P(TransactionTypeTest, TypeStoredCorrectly)
{
    Transaction t("T1", "REF1", GetParam().type, 100.0, 500.0);
    EXPECT_EQ(t.getType(), GetParam().type);
}

INSTANTIATE_TEST_SUITE_P(
    AllTypes,
    TransactionTypeTest,
    ::testing::Values(
        TransactionTypeCase{"DEPOSIT"},
        TransactionTypeCase{"WITHDRAW"},
        TransactionTypeCase{"ACCOUNT OPENING"},
        TransactionTypeCase{"ACCOUNT CLOSURE"}
));
