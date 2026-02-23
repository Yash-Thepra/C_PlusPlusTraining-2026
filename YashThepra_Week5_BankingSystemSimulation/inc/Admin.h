#pragma once
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

    bool authenticate(const std::string &pass) const override;

    std::string getId() const override;

    std::string getMobile() const override;

    std::string getName() const override;

    void menu() override;
};
