#include <iostream>

int main()
{
    int temporaryVariable1 = 10;
    int temporaryVariable2 = 20;
    int *ptr1 = &temporaryVariable1;

    //normal pointer
    *ptr1 = 30;
    std::cout << *ptr1 << "\n";
    std::cout << temporaryVariable1 << "\n";
    ptr1 = &temporaryVariable2;
    std::cout << *ptr1 << "\n";

    //pointer to const
    const int *ptr2 = &temporaryVariable1;
    //*ptr2 = 40;
    std::cout << *ptr2 << "\n";
    ptr2 = &temporaryVariable2;
    std::cout << *ptr2 << "\n";
    
    //constant pointer
    int *const ptr3 = &temporaryVariable1;
    //int const *ptr3 = &temporaryVariable1 is same as const int *ptr3 = &temporaryVariable
    *ptr3 = 50;
    std::cout << *ptr3 << "\n";
    std::cout << temporaryVariable1 << "\n";

    //ptr3 = &temporaryVariable2;
    const int *const ptr4 = &temporaryVariable2;
    std::cout << *ptr4 << "\n";
    //*ptr4 = 60;
    //ptr4 = &temporaryVariable1;
    return 0;
}