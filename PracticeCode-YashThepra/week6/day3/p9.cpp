#include <iostream>

int main()
{
    int x;
    std::cout << "Enter the value of x: ";
    std::cin >> x;
    /*    try
    {
        if (x <= 0)
        {
            throw "value is less than 0.\n";
        }
        std::cout << "The value of x is: " << x << "\n";
    }
    catch(const char* str)
    {
        std::cout << "Exception encountered: " << str;
    }*/

    try
    {
        if (x == 0)
        {
            throw -0.1;
        }
        std::cout << "The value of the x is: " << x << "\n";
    }
    catch(double/*int*/ /*d*/)
    {
        std::cout << "Exception of type double is catched.\n";
    }
    return 0;
}
