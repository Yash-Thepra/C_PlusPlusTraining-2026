#include <cctype>
#include <iostream>

#include "constant.h"
#include "Input.h"

void trimLeadingAndTrailingSpaces(std::string &inputData)
{
    int startIndex = 0;
    while (startIndex < inputData.length() && inputData[startIndex] == ' ')
    {
        startIndex++;
    }
    int endIndex = inputData.length() - 1;
    while (endIndex >= startIndex && inputData[endIndex] == ' ')
    {
        endIndex--;
    }
    int newIndex = 0;
    while (startIndex <= endIndex)
    {
        inputData[newIndex++] = inputData[startIndex++];
    }
    inputData.resize(newIndex);
}

Operation Input::readValidChoice()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimLeadingAndTrailingSpaces(inputData);
        if (inputData.length() == 1 &&
            inputData[0] >= '1' && inputData[0] <= '2')
        {
            int choice = inputData[0] - '0';
            Operation operation = ADDITION;
            if (choice == 2)
            {
                operation = MULTIPLICATION;
            }
            return operation;
        }
        std::cout << "Please follow the below instructions:\n1. Press " << Constant::ADD_OPERATION << " for Addition\n2. Press " << Constant::MULTIPLY_OPERATION << " for Multiplication\n\nEnter: ";
    }
}

bool Input::readValidPreference()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimLeadingAndTrailingSpaces(inputData);
        if (inputData.length() == 1 &&
            inputData[0] >= '1' && inputData[0] <= '2')
        {
            int digit = inputData[0] - '0';
            bool result = false;
            if (digit == 1)
            {
                result = true;
            }
            return result;
        }
        std::cout << "\nInvalid Input! please Try again.\n";
    }
}

double Input::readValidDouble()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimLeadingAndTrailingSpaces(inputData);
        bool flag = true;
        int decimalCount = 0;
        int index = 0;
        if (!inputData.empty() && (inputData[index] == '+' || inputData[index] == '-'))
        {
            index++;
        }
        for (; index < inputData.length(); index++)
        {
            if (isdigit(inputData[index]))
            {
                continue;
            }
            if (inputData[index] == '.' && decimalCount++ == 0)
            {
                continue;
            }
            flag = false;
            break;
        }
        if (!flag || inputData.empty())
        {
            std::cout << "\nInvalid number, Please try again.\n";
            continue;
        }
        double result = 0.0;
        double decimalFactor = 0.1;
        bool fraction = false;
        index = 0;
        if (inputData[index] == '+' || inputData[index] == '-')
        {
            index++;
        }
        for (; index < inputData.length(); index++)
        {
            if (inputData[index] == '.')
            {
                fraction = true;
                continue;
            }
            int digit = inputData[index] - '0';
            if (!fraction)
            {
                result = result * 10 + digit;
            }
            else
            {
                result += digit * decimalFactor;
                decimalFactor /= 10;
            }
        }
        if (inputData[0] == '-')
        {
            result = -result;
        }
        return result;
    }
}

int Input::readValidInteger()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimLeadingAndTrailingSpaces(inputData);
        bool isValidInteger = true;
        for (int index = 0; index < inputData.length(); index++)
        {
            if (!isdigit(inputData[index]))
            {
                isValidInteger = false;
                break;
            }
        }
        if (!isValidInteger || inputData.empty())
        {
            std::cout << "\nInvalid number! Please try again.\n";
            continue;
        }
        int result = 0;
        for (int index = 0; index < inputData.length(); index++)
        {
            int digit = inputData[index] - '0';
            result = result * 10 + digit;
        }
        return result;
    }
}
