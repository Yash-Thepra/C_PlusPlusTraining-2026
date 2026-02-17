#include <iostream>

class A
{
public:
    static void print()
    {
        //std::cout << x << "\n"; can't do since i am static don't have the implicit this pointer
    }

    void print(int num)
    {
        x = num;
        std::cout << x << "\n";
    }

private:
    int x;
};
int main()
{
    A a;
    //a.print(); error
    a.print(10);
    return 0;
}