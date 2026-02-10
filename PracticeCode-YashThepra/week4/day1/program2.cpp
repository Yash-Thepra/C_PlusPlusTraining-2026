#include <iostream>

/*void foo(int arr[]) 
{
    std::cout << sizeof(arr) << "\n";
}*/

void foo2(int (&arr)[10])
{
    std::cout << sizeof(arr) << "\n";
}
int main()
{
    int a[10];
    std::cout << sizeof(a) << "\n";
    //foo(a);
    foo2(a);
    return 0;
}