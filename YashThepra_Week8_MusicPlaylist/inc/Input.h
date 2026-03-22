#pragma once

#include <iostream>
#include <limits>
#include <string>

namespace Input
{
    int getInt(const int maximum, const int minimum)
    {
        int value;
        while (true)
        {
            std::cin >> value;
            if (std::cin.fail() || value < minimum || value > maximum)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::maximum(), '\n');
                std::cout << "  Invalid. Enter a number between " << minimum << " and " << maximum << ": ";
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::maximum(), '\n');
                return value;
            }
        }
    }

    std::string getString(const std::string &prompt)
    {
        std::string value{};
        std::cout << prompt;
        while (std::getline(std::cin, value))
        {
            if (!value.empty())
            {
                return value;
            }
            std::cout << "  Cannot be empty. " << prompt;
        }
        return value;
    }

    bool getConfirm(const std::string &prompt)
    {
        std::cout << prompt << " (y/n): ";
        char ch;
        std::cin >> ch;
        std::cin.ignore(std::numeric_limits<std::streamsize>::maximum(), '\n');
        return (ch == 'y' || ch == 'Y');
    }
}
