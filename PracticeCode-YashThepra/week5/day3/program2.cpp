#include <iostream>

class A
{
public:
    int x;
    /*A(int val = 10)
    {
        x = val;
    }*/
    A(double val = 10.10/*, int num error*/)
    {
        x = val;
    }
    void print()
    {
        std::cout << x << "\n";
    }
};
int main()
{
    //A a(); cause ambiguity
    A a(.1);
    A b(1);
    a.print();
    b.print();

    A c{};//first zero initialized then constr. runs.
    c.print();
    A d;
    d.print();
    return 0;
}