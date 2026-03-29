#include <iostream>

#include "Account.h"
#include "AccountHolder.h"
#include "Bank.h"
#include "constant.h"
#include "Input.h"

AccountHolder::AccountHolder(std::string id, std::string name, std::string mobile, std::string password)
{
    userId = id;
    this->name = name;
    this->mobile = mobile;
    this->password = password;
}

bool AccountHolder::authenticate(const std::string &password) const
{
    return this->password == password;
}

std::string AccountHolder::getId() const
{
    return userId;
}

std::string AccountHolder::getMobile() const
{
    return mobile;
}

std::string AccountHolder::getName() const
{
    return name;
}

void AccountHolder::menu()
{
    Bank &bank = Bank::getInstance();

    while (true)
    {
        std::cout << USER_MENU;
        int choice = Input::readMenuChoice(1, 7);

        Account *account = bank.getAccountByOwner(userId);
        if (choice == 1)
        {
            if (account != nullptr)
            {
                std::cout << "Account already exists.\n";
                continue;
            }
            std::cout << "Enter initial deposit: ";
            double amount = Input::readValidDouble();
            if (amount < MIN_OPENING_BALANCE)
            {
                std::cout << "Minimum opening balance is " << MIN_OPENING_BALANCE << "\n";
                continue;
            }
            bank.createAccount(userId, amount);
            std::cout << "Account created successfully.\n";
        }
        else if (choice == 2)
        {
            if (!account)
            {
                std::cout << "No account found.\n";
                continue;
            }
            std::cout << "Enter amount to deposit: ";
            double amount = Input::readValidDouble();
            if (!account->deposit(amount))
            {
                std::cout << INVALID_AMOUNT;
            }
            else
            {
                std::cout << "Deposit successful.\n";
            }
        }
        else if (choice == 3)
        {
            if (!account)
            {
                std::cout << "No account found.\n";
                continue;
            }
            std::cout << "Enter amount to withdraw: ";
            double amount = Input::readValidDouble();
            if (!account->withdraw(amount))
            {
                std::cout << INSUFFICIENT_BALANCE;
            }
            else
            {
                std::cout << "Withdrawal successful.\n";
            }
        }
        else if (choice == 4)
        {
            if (!account)
            {
                std::cout << "No account found.\n";
                continue;
            }
            std::cout << "Current Balance: " << account->getBalance() << "\n";
        }
        else if (choice == 5)
        {
            if (!account)
            {
                std::cout << "No account found.\n";
                continue;
            }
            account->showMiniStatement();
        }
        else if (choice == 6)
        {
            if (!account)
            {
                std::cout << "No account found.\n";
                continue;
            }
            account->showFullStatement();
        }
        else
        {
            break;
        }
    }
}
