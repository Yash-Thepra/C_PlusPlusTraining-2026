#include <iostream>
#include "AccountHolder.h"
#include "Bank.h"
#include "constants.h"
#include "input.h"

AccountHolder::AccountHolder(std::string id, std::string name, std::string mobile, std::string password) : userId(id), name(name), mobile(mobile), password(password)
{
}

bool AccountHolder::authenticate(const std::string &pass) const
{
    return this->password == pass;
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

std::string AccountHolder::getRole() const 
{ 
    return "Account Holder"; 
}

bool AccountHolder::handleOpenAccount(IBank &bank)
{
    if (bank.getAccountByOwner(userId) != nullptr)
    {
        std::cout << "Account already exists.\n";
        return false;
    }
    std::cout << "Enter initial deposit: ";
    double amount = Input::readValidDouble();
    if (amount < MIN_OPENING_BALANCE)
    {
        std::cout << "Minimum opening balance is " << MIN_OPENING_BALANCE << "\n";
        return false;
    }
    bank.createAccount(userId, amount);
    std::cout << "Account created successfully.\n";
    return true;
}

bool AccountHolder::handleDeposit(IBank &bank)
{
    Account *account = bank.getAccountByOwner(userId);
    if (!account)
    {
        std::cout << "No account found.\n";
        return false;
    }
    std::cout << "Enter amount to deposit: ";
    double amount = Input::readValidDouble();
    if (!account->deposit(amount))
    {
        std::cout << INVALID_AMOUNT;
        return false;
    }
    std::cout << "Deposit successful.\n";
    return true;
}

bool AccountHolder::handleWithdraw(IBank &bank)
{
    Account *account = bank.getAccountByOwner(userId);
    if (!account)
    {
        std::cout << "No account found.\n";
        return false;
    }
    std::cout << "Enter amount to withdraw: ";
    double amount = Input::readValidDouble();
    if (!account->withdraw(amount))
    {
        std::cout << INSUFFICIENT_BALANCE;
        return false;
    }
    std::cout << "Withdrawal successful.\n";
    return true;
}

void AccountHolder::handleViewBalance(IBank &bank)
{
    Account *account = bank.getAccountByOwner(userId);
    if (!account)
    {
        std::cout << "No account found.\n";
        return;
    }
    std::cout << "Current Balance: " << account->getBalance() << "\n";
}

void AccountHolder::handleMiniStatement(IBank &bank)
{
    Account *account = bank.getAccountByOwner(userId);
    if (!account)
    {
        std::cout << "No account found.\n";
        return;
    }
    account->showMiniStatement();
}

void AccountHolder::handleFullStatement(IBank &bank)
{
    Account *account = bank.getAccountByOwner(userId);
    if (!account)
    {
        std::cout << "No account found.\n";
        return;
    }
    account->showFullStatement();
}

void AccountHolder::menu()
{
    Bank &bank = Bank::getInstance();
    while (true)
    {
        std::cout << USER_MENU;
        int choice = Input::readMenuChoice(1, 7);
        if (choice == 1)
        {
            handleOpenAccount(bank);
        }
        else if (choice == 2)
        {
            handleDeposit(bank);
        }
        else if (choice == 3)
        {
            handleWithdraw(bank);
        }
        else if (choice == 4)
        {
            handleViewBalance(bank);
        }
        else if (choice == 5)
        {
            handleMiniStatement(bank);
        }
        else if (choice == 6)
        {
            handleFullStatement(bank);
        }
        else
        {
            break;
        }
    }
}
