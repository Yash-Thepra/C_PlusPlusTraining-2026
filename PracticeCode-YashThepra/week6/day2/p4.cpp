#include <iostream>

class A
{
    int x;
    int y;
public:
    A(int a, int b)
    {
        x = a;
        y = b;
    }
    void print()
    {
        std::cout << "x: " << x << "\n";
        std::cout << "y: " << y << "\n";
    }
};

int main()
{
    A a(10, 11);
    a.print();
    return 0;
}
// debugged this program using gdb