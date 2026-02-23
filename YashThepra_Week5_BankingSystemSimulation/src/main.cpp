#include <iostream>

#include "Bank.h"
#include "AccountHolder.h"
#include "Admin.h"
#include "constant.h"
#include "Input.h"

int main()
{
    Bank &bank = Bank::getInstance();
    bank.addUser(new Admin("ADMIN1", "SuperAdmin", "9999999999", "1234"));
    while (true)
    {
        std::cout << MAIN_MENU;
        int choice = Input::readMenuChoice(1, 3);

        if (choice == 1)
        {
            std::cout << "Enter Name: ";
            std::string name = Input::readNonEmptyString();

            std::cout << "Enter Mobile: ";
            std::string mobile = Input::readValidMobile();

            std::cout << "Enter Password: ";
            std::string password = Input::readValidPassword();

            bank.addUser(new AccountHolder("U" + mobile, name, mobile, password));
        }
        else if (choice == 2)
        {
            std::cout << "Enter Mobile or Account No: ";
            std::string id = Input::readNonEmptyString();

            std::cout << "Enter Password: ";
            std::string password = Input::readValidPassword();

            IUser *user = bank.login(id, password);

            if (user)
            {
                user->menu();
            }
            else
            {
                std::cout << INVALID_CREDENTIALS;
            }
        }
        else if (choice == 3)
        {
            break;
        }
    }
    return 0;
}
