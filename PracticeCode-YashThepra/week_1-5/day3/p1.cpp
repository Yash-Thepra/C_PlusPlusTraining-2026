#include <iostream>

class base 
{
public:
    virtual void print() = 0;
    //{
       // std::cout << "I am abstract.\n";
    //}
    virtual ~base() {}
};

void base::print()
{
    std::cout << "I can define here.\n";
}
class derived : public base
{
public:
    //should define other wise it is also abstract
    void print()
    {
        //std::cout << "I am not abstract.\n";
        base::print();
    }
    ~derived()
    {
        std::cout << "derived destructor.\n";
    }
};
int main()
{
    derived d;
    d.print();
    //base b = d;
    base *b = new derived;
    b->print();
    delete b;
    return 0;
}