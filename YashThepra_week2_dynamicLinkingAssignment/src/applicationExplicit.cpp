#include <dlfcn.h>
#include <iostream>
#include "input.h"
#include "operation.h"

using function = double (*)(double, double);
using divide_func = bool (*)(double, double, double &);

void performOperation(const Operation choice,
                      const double firstNumber,
                      const double secondNumber,
                      function add,
                      function subtract,
                      function multiply,
                      divide_func divide)
{
    double result;

    switch (choice)
    {
    case ADD:
        std::cout << add(firstNumber, secondNumber);
        break;

    case SUBTRACT:
        std::cout << subtract(firstNumber, secondNumber);
        break;

    case MULTIPLY:
        std::cout << multiply(firstNumber, secondNumber);
        break;

    case DIVIDE:
        if (!divide(firstNumber, secondNumber, result))
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
    void *handle = dlopen("./lib/libmathops.so", RTLD_LAZY);
    if (!handle)
    {
        return 1;
    }
    function add = (function)dlsym(handle, "addTwoNumbers");
    function subtract = (function)dlsym(handle, "subtractTwoNumbers");
    function multiply = (function)dlsym(handle, "multiplyTwoNumbers");
    divide_func divide = (divide_func)dlsym(handle, "divideTwoNumbers");

    double firstNumber, secondNumber;
    int choice;

    std::cout << "Enter first number: ";
    firstNumber = getValidDouble();

    std::cout << "Enter second number: ";
    secondNumber = getValidDouble();

    std::cout << "1.Add  2.Sub  3.Mul  4.Div\nChoice: ";
    choice = getValidChoice();

    performOperation(static_cast<Operation>(choice), firstNumber, secondNumber, add, subtract, multiply, divide);

    dlclose(handle);
    return 0;
}
