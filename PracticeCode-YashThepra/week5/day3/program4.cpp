#include <iostream>

class area
{
public:
    int rad;
    area(int rad)
    {
        this->rad = rad;
    }
    void printArea()
    {
        std::cout << 3.14 * rad * rad << "\n";
    }
};

class circle
{
public:
    area a;
    circle(int rad) : a(rad) {}//this initialization call for the class A object is a must otherwise we'll get an error that default constructor is implicitly deleted.
    void print()
    {
        a.printArea();
    }
};

int main()
{
    circle c(10);
    c.print();
    circle d(11);
    d.print();
    return 0;
}