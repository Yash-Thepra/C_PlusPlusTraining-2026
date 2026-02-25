#include <iostream>

class base
{
public:
    base(int x)
    {
        std::cout << x << "\n";
    }
};

class derived1 : virtual public base
{
public:
    derived1(int val1, int val2) : base(val2)
    {
        std::cout << val1 << "\n";
    }
};

class derived2 : virtual public base
{
public:
    derived2(int val1, int val2) : base(val2)
    {
        std::cout << val1 << "\n";
    }
};

class dim : public derived1, derived2
{
public:
    dim(int val1, int val2, int val3) : base(val1), derived1(val2, val3), derived2(val2, val3)
    {
        std::cout << val1 << "\n";
    }
};

int main()
{
    dim d(1, 2, 3);
}