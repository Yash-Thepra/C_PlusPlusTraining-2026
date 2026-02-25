#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "I am A.\n";
    }
    virtual ~A() // if it's not virtul then no destructor call of the derived class will place and can cause us undefined behavirou and memory leak.
    {
        std::cout << "I am dead A.\n";
    }
};

class B : public A
{
public:
    B()
    {
        std::cout << "I am B.\n";
    }
    ~B()
    {
        std::cout << "I am dead B.\n";
    }
};

int main()
{
    A *a = new B();
    delete a;

    B b; //in this call subobject constructor call has been taken place.
    A a2 = b; //only the copy constructor has been called that's why the default constructor  of the a2 has not been called and print statement not executed.
    return 0;
}