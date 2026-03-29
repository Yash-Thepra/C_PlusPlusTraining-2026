#pragma once

#include <string>

#include "User.h"

class Admin : public User
{
    std::string name;
    std::string mobile;
    std::string password;
    std::string id;

public:
    Admin(const std::string &name, const std::string &mobile, const std::string &password, const std::string &id);

    ~Admin();

    UserRole getRole() const override;

    std::string getName() const override;

    std::string getId() const override;

    std::string getMobile() const override;

    std::string getPassword() const override;
};
