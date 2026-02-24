#include <iostream>

class base
{
public:
    void print()
    {
        std::cout << "I am base.\n";
    }
};

class derived : public base
{
public:
    void print()
    {
        std::cout << "I am derived.\n";
    }
    void print2()
    {
        std::cout << "I am derived again.\n";
    }
};

int main()
{
    derived d;
    d.print();
    base b;
    b.print();

    base *b2 = new derived;
    b2->print();
    //b2->print2(); can't
    return 0;
}