#include <iostream>
class A
{
    int x;
public:
    /*A(int val)
    {
        x = val; now default constr. dead.
    }*/
    void print()
    {
        std::cout << x << "\n";
    }
};
int main()
{
    A a;// default
    A b {};// value;
    A c;
    c.print();
    a.print();
    b.print();
    c.print();
    return 0;
}