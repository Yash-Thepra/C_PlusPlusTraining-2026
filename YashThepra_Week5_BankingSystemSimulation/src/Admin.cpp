#include <iostream>

#include "Admin.h"
#include "AccountHolder.h"
#include "Bank.h"
#include "constant.h"
#include "Input.h"

Admin::Admin(std::string id, std::string name, std::string mobile, std::string password)
{
    adminId = id;
    this->name = name;
    this->mobile = mobile;
    this->password = password;
}

bool Admin::authenticate(const std::string &password) const
{
    return this->password == password;
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

void Admin::menu()
{
    Bank &bank = Bank::getInstance();
    while (true)
    {
        std::cout << ADMIN_MENU;
        int choice = Input::readMenuChoice(1, 5);
        if (choice == 1)
        {
            bank.showAllUsers();
        }
        else if (choice == 2)
        {
            bank.showAllAccounts();
        }
        else if (choice == 3)
        {
            std::cout << "Enter Name: ";
            std::string name = Input::readNonEmptyString();
            std::cout << "Enter Mobile: ";
            std::string mobile = Input::readValidMobile();
            std::cout << "Enter Password: ";
            std::string pass = Input::readValidPassword();

            bank.addUser(new AccountHolder("U" + mobile, name, mobile, pass));
        }
        else if (choice == 4)
        {
            std::cout << "Enter User ID: ";
            std::string id = Input::readNonEmptyString();
            bank.deleteUser(id);
        }
    }
}
