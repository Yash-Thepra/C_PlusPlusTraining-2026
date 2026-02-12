#include <iostream>

#include "input.h"

static void trimLeadingAndTrailingSpaces(std::string &inputString)
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

Operation Input::getValidChoice()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);

        trimLeadingAndTrailingSpaces(inputString);

        if (inputString.length() == 1 &&
            inputString[0] >= '1' && inputString[0] <= '2')
        {
            int digit = inputString[0] - '0';

            if (digit == 1)
            {
                return ADDITION;
            }
            else
            {
                return MULTIPLICATION;
            }
        }
        std::cout << "\nInvalid choice, Enter 1 for addition and 2 for multiplication: ";
    }
}

ProgramEnd Input::getValidPreference()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);

        trimLeadingAndTrailingSpaces(inputString);

        if (inputString.length() == 1 &&
            inputString[0] >= '1' && inputString[0] <= '2')
        {
            int digit = inputString[0] - '0';

            if (digit == 1)
            {
                return CONTINUE;
            }
            else
            {
                return EXIT;
            }
        }
        std::cout << "\nInvalid choice, Enter 1 to continue and 2 for exit: ";
    }
}

double Input::getValidDouble()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);

        trimLeadingAndTrailingSpaces(inputString);

        bool flag = true;
        int decimalCount = 0;
        int index = 0;

        if (!inputString.empty() && (inputString[index] == '+' || inputString[index] == '-'))
        {
            index++;
        }

        for (; index < inputString.length(); index++)
        {
            if (isdigit(inputString[index]))
            {
                continue;
            }
            if (inputString[index] == '.' && decimalCount++ == 0)
            {
                continue;
            }
            flag = false;
            break;
        }

        if (!flag || inputString.empty())
        {
            std::cout << "\nInvalid number, Please try again.\n";
            continue;
        }

        double result = 0.0;
        double decimalFactor = 0.1;
        bool fraction = false;

        index = 0;

        if (inputString[index] == '+' || inputString[index] == '-')
        {
            index++;
        }
        for (; index < inputString.length(); index++)
        {
            if (inputString[index] == '.')
            {
                fraction = true;
                continue;
            }
            int digit = inputString[index] - '0';
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

        if (inputString[0] == '-')
        {
            result = -result;
        }
        return result;
    }
}

int Input::getValidInteger()
{
    std::string inputString;

    while (true)
    {
        std::getline(std::cin, inputString);

        trimLeadingAndTrailingSpaces(inputString);

        bool flag = true;

        for (int index = 0; index < inputString.length(); index++)
        {
            if (!isdigit(inputString[index]))
            {
                flag = false;
                break;
            }
        }
        if (!flag || inputString.empty())
        {
            std::cout << "\nInvalid number! Please try again.\n";
            continue;
        }

        int result = 0;

        for (int index = 0; index < inputString.length(); index++)
        {
            int digit = inputString[index] - '0';
            result = result * 10 + digit;
        }
        return result;
    }
}
