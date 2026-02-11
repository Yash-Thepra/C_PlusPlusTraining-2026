#include <iostream>

class A 
{
    private:
    int num;
    public:
    A()
    {
        std::cout << "constructor called" << "\n";
    }
    A(int num)
    {
        this->num = num;
    }
    void print()
    {
        std::cout << num << "\n";
    }
};
int main()
{
    A a;// constructor called at the time of object creation
    //A a(10); give error redeclartion
    A aa(10);
    aa.print();

    A b(aa); // default copy constructor called
    b.print();

    return 0;
}