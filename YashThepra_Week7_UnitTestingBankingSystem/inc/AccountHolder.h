#pragma once

#include "IBank.h"
#include "IUser.h"

class AccountHolder : public IUser
{
private:
    std::string userId;
    std::string name;
    std::string mobile;
    std::string password;

public:
    AccountHolder(std::string id, std::string name, std::string mobile, std::string password);

    bool authenticate(const std::string &password) const override;

    std::string getId() const override;

    std::string getMobile() const override;

    std::string getName() const override;

    std::string getRole() const override;

    void menu() override;

    bool handleOpenAccount(IBank &bank);

    bool handleDeposit(IBank &bank);

    bool handleWithdraw(IBank &bank);

    void handleViewBalance(IBank &bank);

    void handleMiniStatement(IBank &bank);
    
    void handleFullStatement(IBank &bank);
};
