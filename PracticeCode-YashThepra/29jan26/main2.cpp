#include <iostream>
//#include "add2.cpp" give multiple definition error
#include "add2.h"
//int add2(int a, int b, int c);

int main()
{
    std::cout << add2(4, 5, 9);
    return 0;
}