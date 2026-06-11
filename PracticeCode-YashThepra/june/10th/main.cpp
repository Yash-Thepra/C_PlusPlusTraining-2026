#include <iostream>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divd(int a, int b);

int main()
{
    std::cout << "addition: " << add(10, 5) << "\n";
    std::cout << "subtraction: " << sub(10, 5) << "\n";
    std::cout << "multiplication: " << mul(10, 5) << "\n";
    std::cout << "division: " << divd(10, 5) << "\n";
    return 0;
}
