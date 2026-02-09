#include <cctype>
#include <iostream>
#include <string>
#include "input.h"

void trimLeadingAndTrailingSpaces(std::string &inputString)
{
    int startIndex = 0;
    while (startIndex < inputString.length() && inputString[startIndex] == ' ')
    {
        startIndex++;
    }
    int endIndex = inputString.length() - 1;
    while (endIndex >= startIndex && inputString[endIndex] == ' ')
    {
        endIndex--;
    }
    int newIndex = 0;
    while (startIndex <= endIndex)
    {
        inputString[newIndex++] = inputString[startIndex++];
    }
    inputString.resize(newIndex);
}

double getValidDouble()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);
        trimLeadingAndTrailingSpaces(inputString);

        bool flag = true;
        int decimalCount = 0;
        int index = 0;

        if (inputString[index] == '+' || inputString[index] == '-')
        {
            index++;
        }
        for (; index < inputString.length(); index++)
        {
            if (isdigit(inputString[index])) continue;
            if (inputString[index] == '.' && decimalCount++ == 0) continue;
            flag = false;
            break;
        }

        if (!flag|| inputString.empty())
        {
            std::cout << "Invalid number, enter again: ";
            continue;
        }

        double result = 0.0, decimalFactor = 0.1;
        bool fraction = false;
        index = 0;

        if (inputString[index] == '+' || inputString[index] == '-')
            index++;

        for (; index < inputString.length(); index++)
        {
            if (inputString[index] == '.')
            {
                fraction = true;
                continue;
            }
            int digit = inputString[index] - '0';
            if (!fraction)
                result = result * 10 + digit;
            else
            {
                result += digit * decimalFactor;
                decimalFactor /= 10;
            }
        }
        if (inputString[0] == '-')
        {
            result = -result;
        }
        return result;
    }
}

int getValidChoice()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);
        trimLeadingAndTrailingSpaces(inputString);

        if (inputString.length() == 1 &&
            inputString[0] >= '1' && inputString[0] <= '4')
        {
            return inputString[0] - '0';
        }

        std::cout << "Invalid choice, enter 1 to 4: ";
    }
}
