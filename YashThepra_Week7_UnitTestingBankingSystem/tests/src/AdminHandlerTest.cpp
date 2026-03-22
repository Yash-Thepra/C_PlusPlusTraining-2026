#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Admin.h"
#include "MockBank.h"

using ::testing::_;
using ::testing::NiceMock;

class AdminHandlerTest : public ::testing::Test
{
protected:
    NiceMock<MockBank> *mockBank;
    Admin *admin;

    void SetUp() override
    {
        mockBank = new NiceMock<MockBank>();
        admin = new Admin("ADMIN1", "SuperAdmin", "9999999999", "admin1234");
    }

    void TearDown() override
    {
        delete admin;
        delete mockBank;
    }
};

TEST_F(AdminHandlerTest, ViewUsers_CallsShowAllUsersOnce)
{
    EXPECT_CALL(*mockBank, showAllUsers()).Times(1);
    admin->handleViewUsers(*mockBank);
}

TEST_F(AdminHandlerTest, ViewUsers_NeverCallsShowAllAccounts)
{
    EXPECT_CALL(*mockBank, showAllAccounts()).Times(0);
    admin->handleViewUsers(*mockBank);
}

TEST_F(AdminHandlerTest, ViewAccounts_CallsShowAllAccountsOnce)
{
    EXPECT_CALL(*mockBank, showAllAccounts()).Times(1);
    admin->handleViewAccounts(*mockBank);
}

TEST_F(AdminHandlerTest, ViewAccounts_NeverCallsShowAllUsers)
{
    EXPECT_CALL(*mockBank, showAllUsers()).Times(0);
    admin->handleViewAccounts(*mockBank);
}

TEST_F(AdminHandlerTest, AddUser_CallsAddUserOnce)
{
    EXPECT_CALL(*mockBank, addUser(_)).Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_PassesUserWithCorrectId)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return u->getId() == "U9876543210"; })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_PassesUserWithCorrectName)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return u->getName() == "Riya Sharma"; })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_PassesUserWithCorrectMobile)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return u->getMobile() == "9876543210"; })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_PassesUserWithCorrectRole)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return u->getRole() == "Account Holder"; })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_PasswordAuthenticatesCorrectly)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return u->authenticate("pass1234"); })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, AddUser_WrongPasswordDoesNotAuthenticate)
{
    EXPECT_CALL(*mockBank, addUser(::testing::Truly([](IUser *u)
                                                    { return !u->authenticate("wrongpass"); })))
        .Times(1);
    admin->handleAddUser(*mockBank, "Riya Sharma", "9876543210", "pass1234");
}

TEST_F(AdminHandlerTest, DeleteUser_CallsDeleteUserOnce)
{
    EXPECT_CALL(*mockBank, deleteUser("U9876543210")).Times(1);
    admin->handleDeleteUser(*mockBank, "U9876543210");
}

TEST_F(AdminHandlerTest, DeleteUser_CallsDeleteUserWithCorrectId)
{
    EXPECT_CALL(*mockBank, deleteUser("U9999999999")).Times(1);
    admin->handleDeleteUser(*mockBank, "U9999999999");
}

TEST_F(AdminHandlerTest, DeleteUser_NeverCallsAddUser)
{
    EXPECT_CALL(*mockBank, addUser(_)).Times(0);
    admin->handleDeleteUser(*mockBank, "U9876543210");
}
