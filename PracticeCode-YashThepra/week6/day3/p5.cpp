#include <iostream>

int main()
{
    int x;
    std::cin >> x;
    //try block requires one handler
    try
    {
        if (x < 0)
        {
            throw -1;
        }
        std::cout << "Value of x is: " << x;
    }
    catch(...)//can handle of all types
    {
        std::cout << "Unknown error type.\n";
    }
    return 0;
}