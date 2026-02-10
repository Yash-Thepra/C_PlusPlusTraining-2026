#include <iostream>

void check()
{
    int num = 10;
    std::cout << &num << "\n";
}

int main() {
    int a[10];
    // make a pointer which points to the complete array, not only the first element
    // print size of ptr

    /*
    int (&ptr1)[10] = a;
    std::cout << ptr1 << "\n";
    std::cout << sizeof(ptr1) << "\n";
    */
    
    int(*ptr)[10]  = &a;
    std::cout << a << "\n";
    std::cout << &a[0] << "\n";
    std::cout << &a << "\n";
    std::cout << &a + 1 << "\n";
    std::cout << ptr << "\n";
    std::cout << ptr + 1 << "\n";
    std::cout << *ptr << "\n";
    std::cout << &ptr << "\n";

    std::cout << "\n\n\n";
    for (int i = 0; i < 10; i++)
    {
        check();
    }
    return 0;//same address in every each function call
}