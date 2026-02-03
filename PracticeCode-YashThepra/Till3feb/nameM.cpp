#include <iostream>

void add(int a, int b) 
{
    std::cout << (a + b);
}

void add(double a, double b) 
{
    std::cout << (a + b);
}

int main()
{
    add(5, 5);
    std::cout << "\n";
    add(4.9, 5.1);
}
//mangled name for both add functions
//00000000000011f7 T _Z3adddd 
//00000000000011c9 T _Z3addii