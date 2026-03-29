#pragma once

#include <vector>

#include "User.h"

class SalarySystem
{
    static SalarySystem *instance;
    std::vector<User *> users;
    User *currentUser;
    int userCount;
    SalarySystem();

    std::string generateEmployeeId() const;

    User *findUserByMobile(const std::string &mobile) const;

    User *findEmployeeById(const std::string &id) const;

    void adminSection();

    void employeeSection();

    void updatePersonalDetails();

    void addEmployee();

    void updateEmployeeDetails();

    void deleteEmployee();

    void viewEmployeesDetails() const;

    void viewEmployeesSalaries() const;

public:
    ~SalarySystem();

    static SalarySystem *getInstance();

    void start();
};
