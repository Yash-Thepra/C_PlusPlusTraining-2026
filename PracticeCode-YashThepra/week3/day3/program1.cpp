#include <iostream>

int *foo(int n)
{
    int *ptr = &n;
    return ptr;
}//bad practice

int main()
{
    int *temp = foo(10);
    std::cout << temp << "\n";
    std::cout << *temp << "\n";//garbage
    return 0;
}