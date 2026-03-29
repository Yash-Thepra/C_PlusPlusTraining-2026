#pragma once
#include <string>

constexpr int minimumPasswordLength = 8;
constexpr int mobileLength = 10;
const std::string welcome = "\n========================================\n""      Salary Management System\n""========================================\n";
const std::string loginMenu = "\n1. Login\n2. Exit\nEnter choice: ";
const std::string adminMenu = "\n1. Add Employee\n2. Update Employee\n3. View Employees\n4. Delete Employee\n5. View Salaries\n6. Logout\nEnter choice: ";
const std::string employeeMenu = "\n1. View Personal Details\n2. View Salary\n3. Logout\nEnter choice: ";
const std::string invalidInput = "\nInvalid Input! Try again.\n";
const std::string userNotFound = "\nRecord not found!\n";
const std::string successfulEmployeeRegistration = "\nEmployee Registered Sucessfully.\n";
const std::string successfullyLoggedIn = "\nsucessfully Logged In!";
const std::string detailsModificationChoice = "\n Do you want to update personal details? (1-Yes / 2-No): ";
const std::string detailToModify = "\n1 Update Name\n2. Update Mobile\n3. Update Password\n4. Back\nEnter choice: ";
const std::string successfulUpdate = "\n detail updated successfully.\n";
const std::string successfulExecution = "\n Action Performed.\n";
const std::string mobileExists = "\n mobile already exists.\n";