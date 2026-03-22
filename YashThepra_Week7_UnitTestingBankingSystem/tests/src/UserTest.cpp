#include <gtest/gtest.h>

#include "AccountHolder.h"
#include "Admin.h"

class AccountHolderTest : public ::testing::Test
{
protected:
    AccountHolder *holder;

    void SetUp() override
    {
        holder = new AccountHolder("U9876543210", "Riya Sharma", "9876543210", "pass1234");
    }

    void TearDown() override
    {
        delete holder;
    }
};

TEST_F(AccountHolderTest, GetIdReturnsCorrectValue)
{
    EXPECT_EQ(holder->getId(), "U9876543210");
}

TEST_F(AccountHolderTest, GetNameReturnsCorrectValue)
{
    EXPECT_EQ(holder->getName(), "Riya Sharma");
}

TEST_F(AccountHolderTest, GetMobileReturnsCorrectValue)
{
    EXPECT_EQ(holder->getMobile(), "9876543210");
}

TEST_F(AccountHolderTest, GetRoleReturnsAccountHolder)
{
    EXPECT_EQ(holder->getRole(), "Account Holder");
}

TEST_F(AccountHolderTest, AuthenticateReturnsTrueForCorrectPassword)
{
    EXPECT_TRUE(holder->authenticate("pass1234"));
}

class AccountHolderWrongPasswordTest : public ::testing::TestWithParam<std::string>
{
protected:
    AccountHolder *holder;
    void SetUp() override { holder = new AccountHolder("U9876543210", "Riya Sharma", "9876543210", "pass1234"); }
    void TearDown() override { delete holder; }
};

TEST_P(AccountHolderWrongPasswordTest, WrongPasswordReturnsFalse)
{
    EXPECT_FALSE(holder->authenticate(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WrongPasswords,
    AccountHolderWrongPasswordTest,
    ::testing::Values(
        "wrongpass",
        "PASS1234",
        "pass123",
        "pass12345",
        "",
        " ")
);

class AdminTest : public ::testing::Test
{
protected:
    Admin *admin;

    void SetUp() override
    {
        admin = new Admin("ADMIN1", "SuperAdmin", "9999999999", "admin1234");
    }

    void TearDown() override
    {
        delete admin;
    }
};

TEST_F(AdminTest, GetIdReturnsCorrectValue)
{
    EXPECT_EQ(admin->getId(), "ADMIN1");
}

TEST_F(AdminTest, GetNameReturnsCorrectValue)
{
    EXPECT_EQ(admin->getName(), "SuperAdmin");
}

TEST_F(AdminTest, GetMobileReturnsCorrectValue)
{
    EXPECT_EQ(admin->getMobile(), "9999999999");
}

TEST_F(AdminTest, GetRoleReturnsAdmin)
{
    EXPECT_EQ(admin->getRole(), "Admin");
}

TEST_F(AdminTest, AuthenticateReturnsTrueForCorrectPassword)
{
    EXPECT_TRUE(admin->authenticate("admin1234"));
}

TEST_F(AdminTest, AuthenticateReturnsFalseForWrongPassword)
{
    EXPECT_FALSE(admin->authenticate("wrongpass"));
}

TEST_F(AdminTest, AuthenticateReturnsFalseForEmptyPassword)
{
    EXPECT_FALSE(admin->authenticate(""));
}

TEST_F(AdminTest, AuthenticateIsCaseSensitive)
{
    EXPECT_FALSE(admin->authenticate("ADMIN1234"));
}
