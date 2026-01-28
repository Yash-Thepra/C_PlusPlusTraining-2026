#include <iostream>

int main()
{
    int copyInitializer = 2.4;
    std::cout << copyInitializer << "\n";

    int listInitializer1 {2};
    std::cout << listInitializer1 << "\n";

    //but
    //int listInitializer2 {2.4};
    //std::cout << listInitializer2 << "\n"; complilation error for narrowing conversion
    //char temp = 47;
    //std::cout << temp;
}