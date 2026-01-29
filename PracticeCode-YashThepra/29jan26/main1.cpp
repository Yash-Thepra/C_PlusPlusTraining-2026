#include <iostream>
#include "add.h"
//#include "add.h"// header guards will handle double inclusion

int main()
{
    std::cout << add(3, 4);
    return 0;
}