#include <iostream>

class Base
{
public:
    Base() {}
};

class Derived: public Base
{
public:
    Derived() {}
};

int main()
{
    try
    {
        throw Derived();
    }
    catch (const Derived& derived)
    {
        std::cerr << "caught Derived";
    }
    catch (const Base& base)
    {
        std::cerr << "caught Base";
    }
    /*  catch (const Derived& derived)
    {
        std::cerr << "caught Derived";
    }*/
    // we will get an warning and also the exception is caught by the handler because derived is an base to work this as expected we can flip the order of catch handlers.
    return 0;
}