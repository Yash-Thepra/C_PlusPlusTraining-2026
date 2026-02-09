#include "divide.h"

bool divideTwoNumbers(const double firstNumber, const double secondNumber, double &result)
{
    bool divideResult = false;
    if (secondNumber != 0)
    {
        result = firstNumber / secondNumber;
        bool divideResult = true;
    }
    return divideResult;
}
