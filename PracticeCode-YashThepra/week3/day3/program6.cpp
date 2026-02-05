#include <iostream>

int main()
{
    int num = 10;
    int *ptr = &num;

    std::cout << ptr << "\n";
    std::cout << *ptr << "\n\n";

    char ch = 'y';
    char *ptr2 = &ch;

    std::cout << ptr2 << "\n";// it doest not prints the address of the character pointed to instead it prints the character itself
    std::cout << *ptr2 << "\n";
    //it prints the value instead of address because it see's char* as as C-string so it prints characters starting from that memory until it find's zero, sometimes it may print only the assigned character but sometmes it can also prints garbage until it finds the '\0'

    /*char c = 'a';
    //int *ptr3 = &c; invalid
    char *ptr3 = &c;
    std::cout << ptr3 << "\n";*/

    std::cout << (void *)ptr2 << "\n";
    std::cout << static_cast<void *>(ptr2) << "\n";

    int *arr = new int[4];
    char *arr2 = new char[5];

    std::cout << arr << "\n";
    std::cout << arr2 << "\n";


    
    delete [] arr;
    delete [] arr2;

    //char *ptr4 = "abc";error
    char ptr4[5] = "abc"; // prints value
    std::cout << ptr4 << "\n";
    return 0;
}