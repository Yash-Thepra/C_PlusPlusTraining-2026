#include <iostream>

class Animal
{
    public:
    int legs;
    int horns;
};

class cow:public Animal
{
};

int main()
{
    cow c1;
    c1.legs = 4;
    c1.horns = 2;
    std::cout << "cow legs: " << c1.legs << "\n";
    std::cout << "cow horns: " << c1.horns << "\n";
    return 0;
}
