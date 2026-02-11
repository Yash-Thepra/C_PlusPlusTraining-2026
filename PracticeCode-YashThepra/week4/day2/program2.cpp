#include <iostream>

class A
{

};

class B
{
    private:
    int value = 10;
    public:

    void getValue()
    {
        std::cout << value << "\n";
    }
    void setValue(int data)
    {
        value = data;
        std::cout << value << "\n";
    }
};

int main()
{
    A a;
    std::cout << sizeof(a) << "\n";

    B b;
    //b.value;
    b.getValue();
    b.setValue(15);
    b.getValue();//value changed in side the class for the object b.

    //dynamic allocation of object
    B *d = new B;
    (*d).getValue();
    d->getValue();
    delete d;
    return 0;
}