#include <iostream>

#include "../include/add.h"
#include "../include/subtract.h"
#include "../include/multiply.h"
#include "../include/divide.h"
#include "../include/input.h"

void performOperation(double firstNumber, double secondNumber, int choice)
{
    bool flag = true;
    switch (choice)
    {
    case 1:
        std::cout << addTwoNumbers(firstNumber, secondNumber);
        break;
    case 2:
        std::cout << subtractTwoNumbers(firstNumber, secondNumber);
        break;
    case 3:
        std::cout << multiplyTwoNumbers(firstNumber, secondNumber);
        break;
    case 4:
        if (!flag)
        {
            std::cout << "Can't divide by Zero!\n";
            return;
        }
        std::cout << divideTwoNumbers(firstNumber, secondNumber, flag);        
        break;
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
    performOperation(firstNumber, secondNumber, choice);

    return 0;
}
