#include <iostream>

void printAdd(int a, int b)
{
    std::cout << a + b << "\n";
}

void printMul(int a, int b)
{
    std::cout << a * b << "\n";
}

int main()
{
    /*void (*func)(int, int);
    func = printAdd;
    func(10, 90);
    func = printMul;
    func(10, 90);*/
    auto ptr = printAdd;
    ptr(43,10);
}