#include <iostream>
class A
{
    protected:
    int x;
    public: 
    void print()
    {
        x = 5;
        std::cout << x << "\n";
    }
};
class B:public A
{
    int y;
    public:
    void print()
    {
        x = 10;
        std::cout << x << "\n";
    }
};
int main()
{
    A a;
    //a.x;
    B b;
    b.print();//protected can be accessed inside the derived claa
    return 0;
}