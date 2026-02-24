#include <iostream>

class base
{
public:
    int x;
    int y;
    virtual void print()
    {
        std::cout << "I am base.\n";
    }
};
class derived1 : /*private*/ public base
{
public:
    /*virtual - error*/ int a;
    virtual void show()
    {
        std::cout << "I am derived.\n";
    }
};

int main()
{
    base b;
    derived1 d1;
    std::cout << sizeof(b) << "\n";
    std::cout << sizeof(d1) << "\n";
    //base *b2 = new derived1;
    return 0;
}