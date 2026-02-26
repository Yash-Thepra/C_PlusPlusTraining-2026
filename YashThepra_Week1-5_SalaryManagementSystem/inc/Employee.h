#pragma once

#include <string>

#include "EmployeeDetails.h"
#include "User.h"

class Employee : public User
{
    std::string name;
    std::string mobile;
    std::string password;
    std::string id;
    double baseSalary;
    double bonusComponent;
    double calculatedSalary;

public:
    Employee(const EmployeeDetails& data);

    ~Employee();

    UserRole getRole() const;

    std::string getName() const;

    std::string getId() const;

    std::string getMobile() const;

    std::string getPassword() const;

    double getCalculatedSalary() const;

    void updateName(const std::string &newName);

    void updateMobile(const std::string &newMobile);

    void updatePassword(const std::string &newPassword);

    void updateSalary(const double baseSalary, const double bonus);
};
