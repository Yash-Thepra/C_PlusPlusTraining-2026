#include <iostream>

void foo(int num)
{
    int *ptr = new int(num);
    std::cout << "address: " << ptr << " value: " << *ptr << "\n";
    return;
}
int main()
{
    //memory leak
    //one we had already discussed

    /*
    while (some value)
    {
       int *ptr = new int(10);
    }
    */

    //let
    int *ptr = new int(10);
    std::cout << "address: " << ptr << " value: " << *ptr << "\n";

    ptr = new int(12); // memory of first newly created integer inside the heap is leaked because we can't free (lost its track)
    std::cout << "address: " << ptr << " value: " << *ptr << "\n\n";
    foo(12);//memory of dynamically allocated integer is lost
}