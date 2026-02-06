#include <iostream>
#include <cstdlib>

int main()
{
    //int *ptr = new char(5);
    //int *ptr = std::malloc(sizeof(int));
    int *ptr = new int;
    std::cout << *ptr << "\n";
    delete ptr;
    std::cout << *ptr << "\n";
    ptr = nullptr;
    std::cout << ptr << "\n";
    //std::cout << *ptr << "\n"; segmentation fault core dumped

    char *c = new char[4];
    std::cout << c << "\n";

    char *ptr2 = nullptr;
    std::cout << ptr2 << "\n";
    return 0;
}