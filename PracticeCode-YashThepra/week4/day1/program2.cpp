#include <iostream>

/*void foo(int arr[]) 
{
    std::cout << sizeof(arr) << "\n";
}*/

void foo2(int (&arr)[10])
{
    std::cout << sizeof(arr) << "\n";
    std::cout << &arr << "\n";
    std::cout << sizeof(arr + 1) << "\n";
    std::cout << &arr << "\n";
    std::cout << &arr + 1 << "\n";
    std::cout << arr << "\n";
    std::cout << arr + 1 << "\n";
    //std::cout << &(arr + 1) << "\n"; lvalue require unary operand
}
int main()
{
    int a[10];
    std::cout << sizeof(a) << "\n";
    //foo(a);
    //foo2(a);

    std::cout << &a << "\n";
    std::cout << &a[0] << "\n";
    std::cout << sizeof(&a[0]) << "\n";

    foo2(a);
    return 0;
}