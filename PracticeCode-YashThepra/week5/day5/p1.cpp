#include <iostream>

class A
{
public:
    void speak()
    {
        std::cout << "Hello.\n";
    }
};
class B : virtual public A//give error diamont problem but 
{
};

class C : virtual public A
{
};

class D : public C, public B
{

};

int main()
{
    D d;
    d.speak();
    return 0;
}