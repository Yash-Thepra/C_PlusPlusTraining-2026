#include <iostream>

int f1(int x)
{
    if (x == 1)
    {
        throw 2;
    }
    return x;
}

int f2(int x) noexcept
{
    if (x == 1)
    {
        throw 2;
    }
    return x;
}

int main()
{
    int x; 
    std::cin >> x;
    std::cout << "f1 called: " << f1(x) << "\n";
    std::cout << "f2 called: " << f2(x) << "\n";
    //terminates since noexcept throws an exception
    return 0;
}