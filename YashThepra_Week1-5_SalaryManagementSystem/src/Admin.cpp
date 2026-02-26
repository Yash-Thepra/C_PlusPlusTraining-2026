#include <string>

#include "Admin.h"
#include "enums.h"

Admin::Admin(const std::string &adminName, const std::string &adminMobile, const std::string &adminPassword, const std::string &adminId) : name(adminName), mobile(adminMobile), password(adminPassword), id(adminId)
{
}

Admin::~Admin() = default;

UserRole Admin::getRole() const
{
    return ADMIN;
}

std::string Admin::getName() const
{
    return name;
}

std::string Admin::getMobile() const
{
    return mobile;
}

std::string Admin::getPassword() const
{
    return password;
}

std::string Admin::getId() const
{
    return id;
}
