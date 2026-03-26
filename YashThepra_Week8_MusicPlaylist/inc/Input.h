#pragma once

#include <iostream>
#include <limits>
#include <string>

#include "Constant.h"

namespace Input
{
    void trimInputData(std::string &inputData)
    {
        int start = Constant::zero;
        while (start < inputData.length() && inputData[start] == Constant::space)
        {
            start++;
        }
        int end = inputData.length() - Constant::one;
        while (end >= start && inputData[end] == Constant::space)
        {
            end--;
        }
        int index = Constant::zero;
        while (start <= end)
        {
            inputData[index++] = inputData[start++];
        }
        inputData.resize(index);
    }

    int readValidInteger(const int maximum, const int minimum)
    {
        std::string userInput;
        while (true)
        {
            std::getline(std::cin, userInput);

            trimInputData(userInput);
            bool isValid = !userInput.empty();
            for (char temp : userInput)
            {
                if (!std::isdigit(temp) && !(temp == Constant::dashChar && &temp == &userInput[Constant::zero]))
                {
                    isValid = false;
                    break;
                }
            }
            if (isValid)
            {
                try
                {
                    const int value{std::stoi(userInput)};
                    if (value >= minimum && value <= maximum)
                    {
                        return value;
                    }
                }
                catch (...)
                {
                }
            }
            std::cout << Constant::invalidInput << minimum << Constant::andWord << maximum << Constant::colonSpace;
        }
    }

    std::string readNonEmptyString(const std::string &userInput)
    {
        std::string value;
        std::cout << userInput;
        while (std::getline(std::cin, value))
        {
            if (!value.empty())
            {
                return value;
            }
            std::cout << Constant::cannotEmpty << userInput;
        }
        return value;
    }

    bool checkYesOrNo(const std::string &userInput)
    {
        std::cout << userInput << Constant::yesOrNo;
        char ch;
        std::cin >> ch;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), Constant::newLineChar);
        return (ch == Constant::yLower || ch == Constant::yUpper);
    }
}
