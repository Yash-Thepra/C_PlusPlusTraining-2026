#include <iostream>
#include "add.h"
#include "divide.h"
#include "input.h"
#include "multiply.h"
#include "operation.h"
#include "subtract.h"

void performOperation(const double firstNumber,const double secondNumber,const Operation choice)
{
    double result;

    switch (choice)
    {
    case ADD:
        std::cout << addTwoNumbers(firstNumber, secondNumber);
        break;

    case SUBTRACT:
        std::cout << subtractTwoNumbers(firstNumber, secondNumber);
        break;

    case MULTIPLY:
        std::cout << multiplyTwoNumbers(firstNumber, secondNumber);
        break;

    case DIVIDE:
        if (!divideTwoNumbers(firstNumber, secondNumber, result))
        {
            std::cout << "Can't divide by zero!\n";
        }
        else 
        {
            std::cout << result;
        }
        break;
    default:
        std::cout << "Invalid Choice!\n";
    }
}

int main()
{
    double firstNumber, secondNumber;
    int choice;

    std::cout << "Enter first number: ";
    firstNumber = getValidDouble();

    std::cout << "Enter second number: ";
    secondNumber = getValidDouble();

    std::cout << "1.Add  2.Sub  3.Mul  4.Div\nChoice: ";
    choice = getValidChoice();
    performOperation(firstNumber, secondNumber, static_cast<Operation>(choice));

    return 0;
}
