#include <iostream>

class A
{
public:
    int x = 10;
    /*static*/ void print2() // static member functions don't have this.
    {
        std::cout << this->x << "\n";
    }
};
void print(const A &a)
{
    std::cout << a.x << "\n";
}
int main()
{
    A a{10};
    print(a);
    //or can do the same with temporary object.
    print(A {15});
    //or can do the same with implicit conversion
    print({20});
    a.print2();
    return 0;
}