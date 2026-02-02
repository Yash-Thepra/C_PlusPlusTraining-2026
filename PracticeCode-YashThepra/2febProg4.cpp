#include <iostream>

void justPrint(int *ptr)
{
    std::cout << *ptr << "\n";
    std::cout << ptr << "\n";
    *ptr = 2 * (*ptr);
    std::cout << *ptr << "\n";
    ptr++;
    std::cout << ptr << "\n";
}

void deepPrint(int *&ptr)
{
    ptr++; 
}

/*void deepPrint2(const int *ptr)
{
    *ptr = 30;
}*/

int main()
{
    int temp = 10;
    //int ptr = &temp; invalid conversion from int * to int
    //char *ptr = &temp;

    int *ptr = &temp;
    std::cout << sizeof(ptr) << "\n";
    std::cout << sizeof(&temp) << "\n";

    std::cout << "before: " << temp << "\n";
    *ptr = 20;
    std::cout << "after: " << temp << "\n";
    std::cout << "after again: " << *ptr << "\n";

    std::cout << &temp << "\n";
    std::cout << ptr << "\n";
    //ptr++;
    std::cout << ptr << "\n";
    std::cout << *ptr << "\n\n\n";//garbage value
    justPrint(ptr);
    std::cout << ptr << "\n";
    std::cout << temp << "\n\n\n";

    std::cout << "Address before: " << ptr << "\n";
    deepPrint(ptr);
    std::cout << "Address after: " << ptr << "\n";//because passed by reference

    std::cout << "\n\n\n";

    return 0;
}