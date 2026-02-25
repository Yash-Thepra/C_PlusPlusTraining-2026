#include <iostream>

class base
{
    int x = 10;
public:
    /* base(int val)
    {
        x = val;
    }*/
    base& square()
    {
        x = x * x;
        return *this;
    }
    base& square2()
    {
        x = x * x;
        return *this;
    }
    int getX()
    {
        return x;
    }
    void reset()//reseting to default state;
    {
        *this = {/*0*/};
    }
};
int main()
{
    base b/*(10)*/;
    b.square().square2();
    std::cout << b.getX() << "\n";
    b.reset();
    std::cout << b.getX() << "\n";
    return 0;
}