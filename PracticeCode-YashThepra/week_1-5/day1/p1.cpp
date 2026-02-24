#include <iostream>

class base
{
public:
    int x;
    base(int val)
    {
        x = val;
        std::cout << x <<  " base is constructed.\n";
    }
};

class derived : public base
{
public:
    int y;
    derived(int value, int xval) : base{xval}
    {
        y = value;
        //x = 10;
        std::cout << y << " derived is constructed.\n";
    }
};

int main()
{
    //base b;
    derived d(10, 11);
    return 0;
}