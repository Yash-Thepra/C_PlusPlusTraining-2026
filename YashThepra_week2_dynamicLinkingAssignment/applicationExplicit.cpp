#include <iostream>
#include <dlfcn.h>
#include "input.h"

using function = double (*)(double, double);

void performOperation(int choice, double firstNumber, double secondNumber,
                      function add, function subtract, function multiply, function divide)
{
    switch (choice)
    {
    case 1:
        std::cout << add(firstNumber, secondNumber);
        break;
    case 2:
        std::cout << subtract(firstNumber, secondNumber);
        break;
    case 3:
        std::cout << multiply(firstNumber, secondNumber);
        break;
    case 4:
        std::cout << divide(firstNumber, secondNumber);
        break;
    }
}

int main()
{
    void *handle = dlopen("./libmathops.so", RTLD_LAZY);
    if (!handle)
        return 1;

    function add = (function)dlsym(handle, "add");
    function subtract = (function)dlsym(handle, "sub");
    function multiply = (function)dlsym(handle, "mul");
    function divide = (function)dlsym(handle, "divide");

    double firstNumber, secondNumber;
    int choice;

    std::cout << "Enter first number: ";
    firstNumber = getValidDouble();

    std::cout << "Enter second number: ";
    secondNumber = getValidDouble();

    std::cout << "1.Add  2.Sub  3.Mul  4.Div\nChoice: ";
    choice = getValidChoice();

    performOperation(choice, firstNumber, secondNumber, add, subtract, multiply, divide);

    dlclose(handle);
    return 0;
}
