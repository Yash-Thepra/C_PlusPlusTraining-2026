#include <iostream>
#include <cctype>

#include "Constant.h"
#include "Input.h"

void Input::trimInputData(std::string &data)
{
    int start = 0;
    while (start < data.length() && data[start] == ' ')
    {
        start++;
    }
    int end = data.length() - 1;
    while (end >= start && data[end] == ' ')
    {
        end--;
    }
    int index = 0;
    while (start <= end)
    {
        data[index++] = data[start++];
    }
    data.resize(index);
}

int Input::readMenuChoice(const int minimum, const int maximum)
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimInputData(inputData);
        if (inputData.length() == 1 && isdigit(inputData[0]))
        {
            int value = inputData[0] - '0';
            if (value >= minimum && value <= maximum)
            {
                return value;
            }
        }
        std::cout << invalidInput;
    }
}

std::string Input::readNonEmptyString()
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);

        trimInputData(input);

        if (!input.empty())
        {
            return input;
        }
        std::cout << invalidInput;
    }
}

std::string Input::readValidMobile()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimInputData(inputData);
        if (inputData.length() == 10)
        {
            bool valid = true;
            for (int i = 0; i < 10; i++)
            {
                if (!isdigit(inputData[i]))
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                return inputData;
            }
        }
        std::cout << invalidInput;
    }
}

std::string Input::readValidPassword()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimInputData(inputData);
        if (inputData.length() >= minimumPasswordLength)
        {
            return inputData;
        }
        std::cout << invalidInput;
    }
}

double Input::readValidDouble()
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);

        trimInputData(input);
        if (input.empty())
        {
            std::cout << invalidInput;
            continue;
        }
        bool valid = true;
        int decimalCount = 0;
        int index = 0;
        if (input[index] == '+' || input[index] == '-')
        {
            index++;
        }
        for (; index < input.length(); index++)
        {
            if (isdigit(input[index]))
            {
                continue;
            }
            if (input[index] == '.' && decimalCount++ == 0)
            {
                continue;
            }
            valid = false;
            break;
        }
        if (!valid)
        {
            std::cout << invalidInput;
            continue;
        }
        double result = 0.0;
        double factor = 0.1;
        bool fraction = false;
        index = 0;
        if (input[index] == '+' || input[index] == '-')
        {
            index++;
        }
        for (; index < input.length(); index++)
        {
            if (input[index] == '.')
            {
                fraction = true;
                continue;
            }
            int digit = input[index] - '0';
            if (!fraction)
            {
                result = result * 10 + digit;
            }
            else
            {
                result += digit * factor;
                factor /= 10;
            }
        }
        if (input[0] == '-')
        {
            result = -result;
        }
        return result;
    }
}
