#include <iostream>

using namespace std;

struct Base 
{ 
    void f()
    {
        cout<<"Base\n";
    } 
};

struct Derived: Base 
{ 
    void f()
    {
        cout<<"Derived\n";
    } 
};

void test(Base b)
{
    b.f(); 
}

void test(Base* b)
{
    b->f(); 
}

int main()
{
    Derived d;
    test(d);
    test(&d);
    return 0;
}
 