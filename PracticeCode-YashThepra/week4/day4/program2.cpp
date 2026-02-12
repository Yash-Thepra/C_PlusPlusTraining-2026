#include <iostream>

class A
{
public:
    int *ageptr;
    A(int age)
    {
        ageptr = new int();
        *ageptr = age;
    }
    A(A& obj)
    {
        ageptr = new int();
        *ageptr = *obj.ageptr;
    }
    void print()
    {
        std::cout << *ageptr << "\n";
    }
};
int main()
{
    A a(10);
    A b(a);
    a.print();
    b.print();
    std::cout << "\n";
    *b.ageptr = 11;
    a.print();
    b.print();

    
    return 0;
}