#include <iostream>

class base
{
public:
    int x = 10;
    int getval(int val)
    {
        return x + val;
    }
    int getval(int a, int b)
    {
        return x + a + b;
    }
protected:
    void print()
    {
        std::cout << "I am base\n";
    }
};

class derived : public base
{
    using base::x;
    using base::getval; //all overloaded are now private
public:
    using base::print;//no parenthesis here
};
int main()
{
    base b;
    //b.print();
    derived d;
    d.print();

    //std::cout << d.x << "\n";
    std::cout << b.x << "\n";
    std::cout << b.getval(10) << " " << b.getval(15, 20) << "\n";
    //d.getval(10);
    //d.getval(15, 20);
    return 0;
}