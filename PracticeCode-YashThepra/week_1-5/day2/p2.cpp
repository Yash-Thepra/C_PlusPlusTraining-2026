#include <iostream>

class base
{
public:
    virtual void print(int x)
    {
        std::cout << x << " base\n";
    }
    virtual void show()
    {
        std::cout << "base.\n";
    }
};

class derived : public base
{
public:
    void print(double x) //override error
    {
        std::cout << x << " derived\n";
    }
    void show()
    {
        std::cout << "derive.\n";
    }
};
int main()
{
    derived d;
    //d.print(9);

    //base b = d;
    base *b{&d};
    b->print(2);
    b->print(1.2);

    base b2 = d;
    b2.show();
    b->show();
    return 0;
}