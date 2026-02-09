#include <iostream>

int ptr(int *p)
{
    *p = 50;
    return *p;
}

void ptr3(int *p)
{
    int x = 10;
    p = &x;
}

int ref(int &r)
{
    int x = 10;
    //r = &x;
    return r = x;
}

int main()
{
   // const int& ref = 20;
    //std::cout << ref << "\n";
    //ref = 30; error

    //int *p;
    //p = NULL;
    //std::cout << p << "\n";
    int x = 10;
    int *ptr1 = &x;
    std::cout << ptr(&x) << "\n";
    std::cout << ptr(ptr1) << "\n";
    //std::cout << ptr(nullptr) << "\n"; segmentation fault
    //ptr1 = nullptr;
    //std::cout << ptr(ptr1) << "\n";

    std::cout << ptr1 << "\n";
    ptr3(ptr1);
    std::cout << ptr1 << "\n";

    int y = 11;
    int& z = y;
    //int &w = nullptr;

    std::cout << ref(y) << "\n";
    std::cout << ref(z) << "\n";
    
    std::cout << z << "\n";
    std::cout << y << "\n";
    std::cout << &y << "\n";
    std::cout << &z << "\n";
    return 0;
}