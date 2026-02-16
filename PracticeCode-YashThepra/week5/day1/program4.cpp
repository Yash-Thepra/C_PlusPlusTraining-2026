#include <iostream>

class A
{
private:
    int x = 49;

public:
    friend void print(const A& obj);//can access both it's public and private members or member functions.
    friend void B::printB(const A& a);
};

class B
{
public:
    void printB(const A& a)
    {
        //std::cout << a.x << "\n"; won't work because class A hasn't seen the full definition of the B
    }
};

void print(const A &obj)
{
    //std::cout << obj.x << "\n";
}

int main()
{
    A a;
    //print(a);
    return 0;
}