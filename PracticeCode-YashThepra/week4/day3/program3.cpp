#include <iostream>

struct S
{
    int num;
};
struct T:S
{
    int id;
};

class A
{
    int num;
};
class B:A
{
    int id;
};

int main()
{
    T t;
    t.num = 10;
    t.id = 1;//by default inheritence and access

    std::cout << t.num << " " << t.id << "\n";

    B b;
    //b.num = 10; inaccessible
    //b.id = 1;
    return 0;
}