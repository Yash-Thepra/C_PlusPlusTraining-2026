#include <iostream>

class A
{
public:
    int x;
    A(int value)
    {
        x = value;
    }
    A(A &obj)
    {
        std::cout << "I am copy constructor called.\n";
        x = obj.x;
    }
    A&/*&*/ operator=(A &obj) // if we return by value then copy constr. is also called after the assignment operation.
    {
        std::cout << "I am copy assignment called.\n";
        x = obj.x;
        return *this;
    }
};

int main()
{
    A aa{20};
    //A cc{}; no matching function error
    //A bb(); error
    //std::cout << bb.x << "\n";
    std::cout << aa.x << "\n";
    A a(15);
    std::cout << a.x << "\n";
    A b = a;
    std::cout << b.x << "\n";
    A c(10);
    std::cout << c.x << "\n";
    c = a; //it calls both.
    std::cout << c.x << "\n";
    A d(a);
    std::cout << d.x << "\n";

    A e(21);
    A f(33);
    (a = e) = f;//may cause undefined behaviour depending upon the situation.
    std::cout << a.x << " " << e.x << " " << f.x << "\n";
}
