#include <iostream>


/*int* getDanglingPointer()
{
    int localVar = 42;
    // Returning the address of a local variable
    return &localVar;
}*/

int main()
{
    int *ptr = new int(4);
    delete ptr;
    std::cout << ptr << "\n";
    std::cout << *ptr << "\n";//danlging

    //int *ptr2 = getDanglingPointer();
    //std::cout << ptr2 << "\n";
    //std::cout << *ptr2 << "\n";/ address of local var returned warning

    int* danglingPtr;
    {
        int var = 210;
        danglingPtr = &var;
    }
    // Undefined behavior
    //std::cout << danglingPtr << "\n";
    //std::cout << *danglingPtr << "\n";
    return 0;

    void *p;
    //std::cout << p << "\n";
    //std::cout << *p << "\n";
    //std::cout << (int*)p << "\n";
    p = nullptr;
    //std::cout << p << "\n";
    std::cout << p << "\n";
}