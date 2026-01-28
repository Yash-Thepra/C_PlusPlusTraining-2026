#include <iostream>

extern "C" void add(int a, int b)
{
    std::cout << (a + b) << " ";
}

void add(double a, double b)
{
    std::cout << (a + b) << " ";
}

int main()
{
    add(5, 5);
    add(4.3, 2.5);
    return 0;
}
//symbol name of add function in which extern "C" is used is not mangled.