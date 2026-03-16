#include <iostream>
#include "Admin.h"
#include "AccountHolder.h"
#include "Bank.h"
#include "constants.h"
#include "input.h"

Admin::Admin(std::string id, std::string name, std::string mobile, std::string password) : adminId(id), name(name), mobile(mobile), password(password)
{
}

bool Admin::authenticate(const std::string &pass) const
{
    return this->password == pass;
}

std::string Admin::getId() const 
{ 
    return adminId; 
}

std::string Admin::getMobile() const 
{ 
    return mobile; 
}

std::string Admin::getName() const 
{ 
    return name; 
}

std::string Admin::getRole() const 
{ 
    return "Admin"; 
}

void Admin::handleViewUsers(IBank &bank)
{
    bank.showAllUsers();
}

void Admin::handleViewAccounts(IBank &bank)
{
    bank.showAllAccounts();
}

void Admin::handleAddUser(IBank &bank, const std::string &name, const std::string &mobile, const std::string &password)
{
    bank.addUser(new AccountHolder("U" + mobile, name, mobile, password));
}

void Admin::handleDeleteUser(IBank &bank, const std::string &userId)
{
    bank.deleteUser(userId);
}

void Admin::menu()
{
    Bank &bank = Bank::getInstance();
    while (true)
    {
        std::cout << ADMIN_MENU;
        int choice = Input::readMenuChoice(1, 5);
        if (choice == 1)
        {
            handleViewUsers(bank);
        }
        else if (choice == 2)
        {
            handleViewAccounts(bank);
        }
        else if (choice == 3)
        {
            std::cout << "Enter Name: ";
            std::string uName = Input::readNonEmptyString();
            std::cout << "Enter Mobile: ";
            std::string uMobile = Input::readValidMobile();
            std::cout << "Enter Password: ";
            std::string uPass = Input::readValidPassword();
            handleAddUser(bank, uName, uMobile, uPass);
        }
        else if (choice == 4)
        {
            std::cout << "Enter User ID: ";
            std::string id = Input::readNonEmptyString();
            handleDeleteUser(bank, id);
        }
        else
        {
            break;
        }
    }
}
