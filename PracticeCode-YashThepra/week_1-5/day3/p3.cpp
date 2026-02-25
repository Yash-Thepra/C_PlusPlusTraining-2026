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
        std::cout << "I am derived.\n";
    }
};

void show1(base/*&*/ b)
{
    b.print();
}
void show2(base *b)
{
    b->print();
}
int main()
{
    derived d;
    base b = d;
    b.print();
    base *B = new derived;
    B->print();

    show1(d);
    derived *d2 = new derived;
    show2(d2);
    return 0;
}