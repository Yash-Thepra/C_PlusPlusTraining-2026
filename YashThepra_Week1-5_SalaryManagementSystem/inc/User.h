#pragma once

#include <string>

#include "enums.h"

class User
{
public:
    virtual ~User() = default;

    virtual UserRole getRole() const = 0;

    virtual std::string getName() const = 0;

    virtual std::string getId() const = 0;

    virtual std::string getMobile() const = 0;

    virtual std::string getPassword() const = 0;
};
