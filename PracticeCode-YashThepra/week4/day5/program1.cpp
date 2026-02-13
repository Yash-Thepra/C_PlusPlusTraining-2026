#include <iostream>

class A
{
    const int x;
    const int y;
    public:
    /*A()
    {
        x = 10; 
        y = 11;error
    }*/

    A():x(y), y(2)//x(10), y(11)
    {
        
    }
    void print()
    {
        std::cout << x << " " << y << "\n";
    }

};

class B
{
    int x;
public:
    B(int num)
    {
        x = num;
    }
    void print()
    {
        std::cout << "\n";
    }
};
class C:public B
{
public:
     C():B(10)
     {

     }
};
int main()
{
    A a;;
    a.print();
    //B b;
    C c;
    return 0;
}