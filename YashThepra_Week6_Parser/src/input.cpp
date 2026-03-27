#include <iostream>
#include <cctype>

#include "Constants.h"
#include "input.h"

void Input::trimInputData(std::string &inputData)
{
    int start = 0;
    while (start < inputData.length() && inputData[start] == ' ')
    {
        start++;
    }
    int end = inputData.length() - 1;
    while (end >= start && inputData[end] == ' ')
    {
        end--;
    }
    int index = 0;
    while (start <= end)
    {
        inputData[index++] = inputData[start++];
    }
    inputData.resize(index);
}

int Input::readMenuChoice(const int minimum, const int maximum)
{
    std::string inputData;

    while (true)
    {
        std::cout << Constants::ENTER_CHOICE;
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
        std::cout << Constants::INVALID_INPUT;
    }
}

std::string Input::readNonEmptyString()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);

        trimInputData(inputData);

        if (!inputData.empty())
        {
            return inputData;
        }
        std::cout << Constants::INVALID_INPUT;
    }
}
