#pragma once

#include <string>

class IUser
{
public:
    virtual ~IUser() {}
    virtual bool authenticate(const std::string &pass) const = 0;
    virtual std::string getId() const = 0;
    virtual std::string getMobile() const = 0;
    virtual std::string getName() const = 0;
    virtual void menu() = 0;
};
