#include <iostream>

class A
{
    double x;
    int y;
public:
    A(int val)
    {
        y = val;
    }
    /*A(double data) : x(data)
    {
        A(10);//don't work as expected instead makes temporary object
    }*/
    A(double data): /*x(data)- will give error*/ A(10) // this will work
    {
        x = data;
    }
    void print()
    {
        std::cout << x << " " << y << "\n";
    }
};
int main()
{
    A a(11.3);
    a.print();
    return 0;
}