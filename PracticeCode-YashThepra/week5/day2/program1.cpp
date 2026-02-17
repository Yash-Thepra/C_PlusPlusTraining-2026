#include <iostream>
class Base
{
public:
    void print()
    {
        std::cout << "I am the base\n";
        std::cout << x << "\n";
    }

private:
    int x = 10;
};

class derived:/*public*/ Base
{
public:
    void print()
    {
        std::cout << "I am the derived.\n";
        std::cout << x << "\n";
    }

private:
    int x = 10;
};

/*void prints(Base& obj)
{
    obj.print();
}*/
void prints2(derived& obj)
{
    std::cout << "Derived via non member function\n";
    obj.print();
}
int main()
{
    derived d;
    //prints(d);
    d.print();
    prints2(d);
    return 0;
}