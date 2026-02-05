#include <iostream>

int main()
{
    int x = 10;
    int& ref = x;
    //int& ref1 = 10; must be an lvalue
    //but
    const int& ref2 = 40;
    std::cout << ref2 << "\n";
    std::cout << &ref2 << "\n";

    //ref2 = 10; error
    return 0;
}