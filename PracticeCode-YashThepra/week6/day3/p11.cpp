#include <iostream>

class dummy
{
    dummy() = delete;
};

int main()
{
    int x;
    std::cin >> x;
    try
    {
        if (x == 1)
        {
            throw "Exception occured.\n";
        }
        std::cout << "Value of x is: " << x << "\n";
    }
    #ifndef NDEBUG
    catch(...)
    {
        std::cout << "Unknow Exception handled.\n";
    }
    #else
    catch(dummy)
    {
        std::cout << "this can never handle since the class dummy can never be instantiated.\n";
    }
    #endif
    return 0;
}