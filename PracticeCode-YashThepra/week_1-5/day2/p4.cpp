#include <iostream>

class base
{
public:
    virtual ~base()
    {
        std::cout << "base.\n";
    }
};

class derived : public base
{
public:
    ~derived()
    {
        std::cout << "derived.\n";
    }
};
int main()
{
    base *b = new derived;
    delete b;
    std::cout << sizeof(*b) << "\n";
    derived d;
    std::cout << sizeof(d) << "\n";
    std::cout << " ";

    return 0;
}