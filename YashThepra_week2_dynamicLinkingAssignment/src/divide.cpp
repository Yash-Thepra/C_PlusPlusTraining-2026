#include "divide.h"

bool divideTwoNumbers(const double firstNumber, const double secondNumber, double &result)
{
    if (secondNumber == 0)
    {
        return false;
    }

    result = firstNumber / secondNumber;
    return true;
}

