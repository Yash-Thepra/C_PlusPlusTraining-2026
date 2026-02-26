#include <iostream>

class base
{
public:
    int x;
    base(int val) : x(val) {}
    virtual void print() const
    {
        std::cout << x << "\n";
    }
};

class derived : public base
{
public:
    derived(int val2) : base(val2) {}
    void print() /*override-> this gives the error*/
    {
        std::cout << "I am base but not overriden.\n";
    }
};
int main()
{
    base * b = new derived(11);
    //b->print(); it prints just the value of the x in base since because of the const nature can't override and consider it's and different but we can do that we can put override there so we can get alleat error.
    return 0;
}