#include<iostream>

struct B
{
    double d;
    int c;
    char a;
    char b;
};

struct C 
{
    double d;
    char a;
    char b;
    char c;
};

struct D {
    char a;
    int b;
    char c;
};
struct E {
    char a;
    char b;
    int c;
};

int main() 
{
    B b;
    std::cout << "Size of structure object: " << sizeof(b) << "\n";
    // if we change some data types
    C c;
    std::cout << "Size of second structure object: " << sizeof(c) << "\n";

    D d;
    E e;
    //the difference in sturct consisting of same data type but different size
    std::cout << "\nSize of object d: " << sizeof(d);
    std::cout << "\nSize of object e: " << sizeof(e);
    return 0;
}