#include <iostream>

class Base
{
public:
    Base() {}
};

class Derived : public Base
{
public:
    Derived() {}

    /*Derived(const Derived&) = delete; */ // error because of stack unwidning
};

int main()
{
    Derived d{};

    try
    {
        throw d; 
    }
    catch (const Derived& derived)
    {
        std::cerr << "caught Derived";
    }
    catch (const Base& base)
    {
        std::cerr << "caught Base";
    }

    return 0;
}