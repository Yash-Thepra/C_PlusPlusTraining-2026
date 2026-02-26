#include <iostream>

class base
{
public:
    virtual void print()
    {
        std::cout << "I am base.\n";
    }
};

class derived : public base
{
public:
    void print()
    {
        std::cout << "but, I am derived.\n";
    }
    void show()
    {
        std::cout << "no if and but, I am derived.\n";
    }
};

int main()
{
    base *b = new derived;
    b->print();
    //b->show(); can't call dervied's function.
    return 0;
}
