#pragma once

#include "IBank.h"
#include "IUser.h"

class Admin : public IUser
{
private:
    std::string adminId;
    std::string name;
    std::string mobile;
    std::string password;

public:
    Admin(std::string id, std::string name, std::string mobile, std::string password);

    bool authenticate(const std::string &password) const override;

    std::string getId() const override;

    std::string getMobile() const override;

    std::string getName() const override;

    std::string getRole() const override;

    void menu() override;

    void handleViewUsers(IBank &bank);

    void handleViewAccounts(IBank &bank);

    void handleAddUser(IBank &bank, const std::string &name,const std::string &mobile, const std::string &password);

    void handleDeleteUser(IBank &bank, const std::string &userId);
};
