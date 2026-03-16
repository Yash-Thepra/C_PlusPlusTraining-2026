#include <iostream>
#include <cctype>

#include "constants.h"
#include "input.h"
 
void Input::trimInputData(std::string &data)
{
    int start = 0;
    while (start < (int)data.length() && data[start] == ' ') 
    {
        start++;
    }
    int end = (int)data.length() - 1;
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
 
int Input::readMenuChoice(int minimum, int maximum)
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
        std::cout << INVALID_INPUT;
    }
}
 
std::string Input::readNonEmptyString()
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);
        trimInputData(input);
        if (!input.empty()) return input;
        std::cout << INVALID_INPUT;
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
                if (!isdigit(inputData[i])) { valid = false; break; }
            }
            if (valid) return inputData;
        }
        std::cout << INVALID_INPUT;
    }
}
 
std::string Input::readValidPassword()
{
    std::string inputData;
    while (true)
    {
        std::getline(std::cin, inputData);
        trimInputData(inputData);
        if ((int)inputData.length() >= MIN_PASSWORD_LENGTH)
        {
            return inputData;
        }
        std::cout << INVALID_INPUT;
    }
}
 
double Input::readValidDouble()
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);
        trimInputData(input);
        if (input.empty()) { std::cout << INVALID_NUMBER; continue; }
 
        bool valid = true;
        int  decimalCount = 0;
        int  idx = 0;
        if (input[idx] == '+' || input[idx] == '-') idx++;
        for (; idx < (int)input.length(); idx++)
        {
            if (isdigit(input[idx])) continue;
            if (input[idx] == '.' && decimalCount++ == 0) continue;
            valid = false;
            break;
        }
        if (!valid) { std::cout << INVALID_NUMBER; continue; }
 
        double result = 0.0, factor = 0.1;
        bool   fraction = false;
        idx = 0;
        if (input[idx] == '+' || input[idx] == '-') idx++;
        for (; idx < (int)input.length(); idx++)
        {
            if (input[idx] == '.') { fraction = true; continue; }
            int digit = input[idx] - '0';
            if (!fraction) result = result * 10 + digit;
            else           { result += digit * factor; factor /= 10; }
        }
        if (input[0] == '-') result = -result;
        return result;
    }
}
 