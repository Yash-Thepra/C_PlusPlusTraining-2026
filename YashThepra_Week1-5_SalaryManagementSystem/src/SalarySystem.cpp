#include <iostream>

#include "Admin.h"
#include "Constant.h"
#include "Employee.h"
#include "EmployeeDetails.h"
#include "Input.h"
#include "SalarySystem.h"

SalarySystem *SalarySystem::instance = nullptr;

SalarySystem::SalarySystem()
{
    currentUser = nullptr;
    userCount = 1;
    users.push_back(new Admin("Yash", "7597660750", "admin_yash", "A1"));
}

SalarySystem::~SalarySystem()
{
    for (int index = 0; index < users.size(); index++)
    {
        delete users[index];
    }
}

SalarySystem *SalarySystem::getInstance()
{
    if (!instance)
    {
        instance = new SalarySystem();
    }
    return instance;
}

std::string SalarySystem::generateEmployeeId() const
{
    return "ITT" + std::to_string(userCount);
}

User *SalarySystem::findUserByMobile(const std::string &mobile) const
{
    User *user = nullptr;
    for (int index = 0; index < users.size(); index++)
    {
        if (users[index]->getMobile() == mobile)
        {
            user = users[index];
            break;
        }
    }
    return user;
}

User *SalarySystem::findEmployeeById(const std::string &id) const
{
    User *user = nullptr;
    for (int index = 0; index < users.size(); index++)
    {
        if (users[index]->getId() == id && users[index]->getRole() == EMPLOYEE)
        {
            user = users[index];
            break;
        }
    }
    return user;
}

void SalarySystem::addEmployee()
{
    userCount++;
    std::string name, mobile, password;
    double baseSalary, bonus;

    std::cout << "Enter Name: ";
    name = Input::readNonEmptyString();

    std::cout << "Enter Mobile: ";
    mobile = Input::readValidMobile();

    if (findUserByMobile(mobile))
    {
        std::cout << mobileExists;
        return;
    }
    std::cout << "Enter Password: ";
    password = Input::readValidPassword();

    std::cout << "Enter Base Salary: ";
    baseSalary = Input::readValidDouble();

    std::cout << "Enter Bonus: ";
    bonus = Input::readValidDouble();

    EmployeeDetails data;

    data.name = name;
    data.mobile = mobile;
    data.password = password;
    data.id = generateEmployeeId();
    data.baseSalary = baseSalary;
    data.bonus = bonus;
    users.push_back(new Employee(data));
    std::cout << successfulEmployeeRegistration;
}

void SalarySystem::updateEmployeeDetails()
{
    std::cout << "Enter Employee ID: ";
    std::string id = Input::readNonEmptyString();

    User *user = findEmployeeById(id);
    if (!user)
    {
        std::cout << userNotFound;
        return;
    }
    double baseSalary, bonus;
    std::cout << "Enter New Base Salary: ";
    baseSalary = Input::readValidDouble();

    std::cout << "Enter New Bonus: ";
    bonus = Input::readValidDouble();

    Employee *emp = (Employee *)user;
    emp->updateSalary(baseSalary, bonus);
    std::cout << successfulExecution;
}

void SalarySystem::deleteEmployee()
{
    std::cout << "Enter Employee ID: ";
    std::string id = Input::readNonEmptyString();
    bool recordCheck = false;
    for (int index = 0; index < users.size(); index++)
    {
        if (users[index]->getId() == id &&
            users[index]->getRole() == EMPLOYEE)
        {
            recordCheck = true;
            delete users[index];
            users.erase(users.begin() + index);
            std::cout << successfulExecution;
            return;
        }
    }
    if (!recordCheck)
    {
        std::cout << userNotFound;
    }
}

void SalarySystem::viewEmployeesDetails() const
{
    for (int index = 0; index < users.size(); index++)
    {
        std::cout << "\nID: " << users[index]->getId() << "\nName: " << users[index]->getName() << "\nMobile: " << users[index]->getMobile() << "\n";
    }
}

void SalarySystem::viewEmployeesSalaries() const
{
    for (int index = 0; index < users.size(); index++)
    {
        if (users[index]->getRole() == EMPLOYEE)
        {
            Employee *emp = (Employee *)users[index];
            std::cout << emp->getName() << " Salary: " << emp->getCalculatedSalary() << "\n";
        }
    }
}

void SalarySystem::start()
{
    std::cout << welcome;

    while (true)
    {
        std::cout << loginMenu;
        int choice = Input::readMenuChoice(1, 2);

        if (choice == 2)
        {
            break;
        }
        std::string mobile, password;
        std::cout << "Enter Mobile: ";
        mobile = Input::readValidMobile();

        std::cout << "Enter Password: ";
        password = Input::readValidPassword();

        User *user = findUserByMobile(mobile);
        if (!user || user->getPassword() != password)
        {
            std::cout << invalidInput;
            continue;
        }
        currentUser = user;
        std::cout << successfullyLoggedIn;

        if (user->getRole() == ADMIN)
        {
            adminSection();
        }
        else
        {
            employeeSection();
        }
    }
}

void SalarySystem::adminSection()
{
    while (true)
    {
        std::cout << adminMenu;
        int choice = Input::readMenuChoice(1, 6);

        if (choice == 6)
        {
            Employee *emp = (Employee *)currentUser;
            break;
        }
        if (choice == 1)
        {
            addEmployee();
        }
        else if (choice == 2)
        {
            updateEmployeeDetails();
        }
        else if (choice == 3)
        {
            viewEmployeesDetails();
        }
        else if (choice == 4)
        {
            deleteEmployee();
        }
        else if (choice == 5)
        {
            viewEmployeesSalaries();
        }
    }
}

void SalarySystem::employeeSection()
{
    while (true)
    {
        std::cout << employeeMenu;
        int choice = Input::readMenuChoice(1, 3);
        if (choice == 3)
        {
            break;
        }
        if (choice == 1)
        {
            std::cout << "\nID: " << currentUser->getId() << "\nName: " << currentUser->getName() << "\nMobile: " << currentUser->getMobile() << "\n";
            std::cout << detailsModificationChoice;
            int updateChoice = Input::readMenuChoice(1, 2);
            if (updateChoice == 1)
            {
                updatePersonalDetails();
            }
        }
        if (choice == 2)
        {
            Employee *emp = (Employee *)currentUser;
            std::cout << "\nCalculated Salary: " << emp->getCalculatedSalary() << "\n";
        }
    }
}

void SalarySystem::updatePersonalDetails()
{
    std::cout << detailToModify;
    int choice = Input::readMenuChoice(1, 4);

    if (choice == 4)
    {
        return;
    }
    Employee *emp = (Employee *)currentUser;
    if (choice == 1)
    {
        std::cout << "Enter New Name: ";
        std::string name = Input::readNonEmptyString();
        emp->updateName(name);
        std::cout << successfulUpdate;
    }
    if (choice == 2)
    {
        std::cout << "Enter New Mobile: ";
        std::string mobile = Input::readValidMobile();

        if (findUserByMobile(mobile))
        {
            std::cout << mobileExists;
            return;
        }
        emp->updateMobile(mobile);
        std::cout << successfulUpdate;
    }
    if (choice == 3)
    {
        std::cout << "Enter New Password: ";
        std::string password = Input::readValidPassword();
        emp->updatePassword(password);
        std::cout << successfulUpdate;
    }
}
