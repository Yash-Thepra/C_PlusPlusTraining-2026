#pragma once
#include <string>

const int MAX_USERS = 20;
const int MAX_ACCOUNTS = 20;
const int MAX_TRANSACTIONS = 100;

const double MIN_OPENING_BALANCE = 500.0;
const int MIN_PASSWORD_LENGTH = 4;

const std::string MAIN_MENU =
    "\n===== BANK SYSTEM =====\n"
    "1. Register\n"
    "2. Login\n"
    "3. Exit\n"
    "Enter choice: ";

const std::string ADMIN_MENU =
    "\n===== ADMIN MENU =====\n"
    "1. View Users\n"
    "2. View Accounts\n"
    "3. Add User\n"
    "4. Delete User\n"
    "5. Logout\n"
    "Enter choice: ";

const std::string USER_MENU =
    "\n===== USER MENU =====\n"
    "1. Open Account\n"
    "2. Deposit\n"
    "3. Withdraw\n"
    "4. View Balance\n"
    "5. Mini Statement\n"
    "6. Full Statement\n"
    "7. Logout\n"
    "Enter choice: ";

const std::string INVALID_INPUT = "Invalid input! Try again: ";
const std::string INVALID_NUMBER = "Invalid number! Try again: ";
const std::string INVALID_CREDENTIALS = "Invalid credentials!\n";
const std::string INVALID_AMOUNT = "Amount must be greater than zero.\n";
const std::string INSUFFICIENT_BALANCE = "Insufficient balance!\n";
