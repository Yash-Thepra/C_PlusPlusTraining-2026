#include <iostream>
#include <cmath>

void trimLeadingAndTrailingSpaces(std::string &inputString)
{
    int startIndex = 0;

    while (startIndex < inputString.length() && inputString[startIndex] == ' ')
    {
        startIndex++;
    }

    int endIndex = inputString.length() - 1;

    while (endIndex >= 0 && inputString[endIndex] == ' ')
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

void handlesExponentCase(std::string inputString, double &result, int index) 
{
    index++;
    bool isExponentNegative = false;
    if (index < inputString.length() && inputString[index] == '+') 
    {
        index++;
    }
    else if (index < inputString.length() && inputString[index] == '-') 
    { 
        isExponentNegative = true; 
        index++; 
    }
    int exponent = 0;
    bool hasDigits = false;
    while (index < inputString.length() && isdigit(inputString[index]))
    {
        exponent = exponent * 10 + (inputString[index] - '0');
        hasDigits = true;
        index++;
    }
    if (hasDigits)
    {
        if (isExponentNegative) 
        {
            exponent = -exponent;
        }
        result *= std::pow(10, exponent);
    }
}
double convertStringToDouble(const std::string inputString)
{
    if (inputString.empty())
    {
        return 0.0;
    }
    int index = 0;
    bool isNegative = false, fractionPart = false;
    double result = 0.0, decimalFactor = 0.1;
    if (inputString[index] == '+')
    {
        index++;
    }
    else if (inputString[index] == '-')
    {
        isNegative = true;
        index++;
    }
    while (index < inputString.length() && (isdigit(inputString[index]) || inputString[index] == '.'))
    {
        if (inputString[index] == '.')
        {
            if (fractionPart)
            {
                break;
            }
            fractionPart = true;
        }
        else
        {
            int digit = inputString[index] - '0';
            if (!fractionPart)
            {
                result = result * 10 + digit;
            }
            else
            {
                result += digit * decimalFactor;
                decimalFactor /= 10;
            }
        }
        index++;
    }
    if (index < inputString.size() && (inputString[index] == 'e' || inputString[index] == 'E'))
    {
        handlesExponentCase(inputString, result, index);
    }
    if (isNegative)
    {
        result = -result;
    }
    return result;
}

int main()
{
    std::string doubleNumber;
    std::cout << "Please Enter the the floating point Number in the string form which is to be converted into double: ";
    trimLeadingAndTrailingSpaces(doubleNumber);
    getline(std::cin, doubleNumber);
    
    std::cout << convertStringToDouble(doubleNumber);
    return 0;
}
