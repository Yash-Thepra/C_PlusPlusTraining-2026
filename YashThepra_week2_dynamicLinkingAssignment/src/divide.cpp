#include "../include/divide.h"

double divideTwoNumbers(double firstNumber, double secondNumber, bool &flag)
{
    if (secondNumber == 0)
    {
        flag = false;
        return -1;
    }

    return firstNumber / secondNumber;
}
