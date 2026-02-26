#include <string>

#include "EmployeeDetails.h"
#include "Employee.h"
#include "enums.h"

Employee::Employee(const EmployeeDetails& data)
    : name(data.name),
      mobile(data.mobile),
      password(data.password),
      id(data.id),
      baseSalary(data.baseSalary),
      bonusComponent(data.bonus)
{
    calculatedSalary = baseSalary + bonusComponent;
}

Employee::~Employee() = default;

UserRole Employee::getRole() const
{
    return EMPLOYEE;
}

std::string Employee::getName() const
{
    return name;
}

std::string Employee::getMobile() const
{
    return mobile;
}

std::string Employee::getPassword() const
{
    return password;
}

std::string Employee::getId() const
{
    return id;
}

double Employee::getCalculatedSalary() const
{
    return calculatedSalary;
}

void Employee::updateSalary(const double baseSalary, const double bonus)
{
    this->baseSalary = baseSalary;
    bonusComponent = bonus;
    calculatedSalary = baseSalary + bonus;
}

void Employee::updateName(const std::string &newName)
{
    name = newName;
}

void Employee::updateMobile(const std::string &newMobile)
{
    mobile = newMobile;
}

void Employee::updatePassword(const std::string &newPassword)
{
    password = newPassword;
}
