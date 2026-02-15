#include <iostream>

class test
{
public:
    int x;
    int y;
    // std::cout << x;
    // x = 5 + 7;
    void func()
    {
        print();
    }
    void print()
    {
        std::cout << "I defined here.\n";
    }
    void print2()
    {
        std::cout << later << "\n";
    }
    int later = 10;

    int a = b;
    int b = 23;
    void print3()
    {
        std::cout << a << "sefs" << "\n";
    }
};
int main()
{
    test itt;
    itt.print();
    itt.func();
    itt.print2();
    itt.print3();//undefined behaviour
    itt.print3();
    itt.print3();
    return 0;
}