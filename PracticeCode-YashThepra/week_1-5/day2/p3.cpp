#include <iostream>

class base
{
public:
    virtual base* getThis()
    {
        std::cout << "base called.\n";
        return this;
    }
    void print()
    {
        std::cout << "base.\n";
    }
};

class derived : public base
{
public:
    derived* getThis() //override not needed in this case.
    {
        std::cout << "derived called.\n";
        return this;
    }
    void print()
    {
        std::cout << "derived.\n";
    }
};

int main()
{
    derived d;
    d.getThis()->print();
    base b = d;
    b.getThis()->print();

    base *b2 {&d};
    b2->getThis()->print();
}