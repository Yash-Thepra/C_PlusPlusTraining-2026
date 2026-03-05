#include <cmath>
#include <iostream>

double mySqrt(double x)
{
    if (x < 0.0)
        throw "Can not take sqrt of negative number";

    return std::sqrt(x);
}

int main()
{
    std::cout << "Enter a number: ";
    double x{};
    std::cin >> x;
    double d = mySqrt(x);
    std::cout << "The sqrt of " << x << " is " << d << '\n';
    /*    try
    {
        double d = mySqrt(x);
        std::cout << "The sqrt of " << x << " is " << d << '\n';
    }
    catch (const char *exception) // catch exceptions of type const char*
    {
        std::cerr << "Error: " << exception << std::endl;
    }
    */
    return 0;
}