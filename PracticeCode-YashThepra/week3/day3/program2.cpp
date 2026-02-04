#include <iostream>

int main()
{
    //differece between static and dynamic memor allocation
    int temp1 = 10;//static
    int *temp2 = new int(11);//dynamic

    std::cout << temp1 << "\n";
    std::cout << *temp2 << "\n";
    std::cout << sizeof(temp2) << "\n";
    delete temp2;

    int n;
    std::cin >> n;
    //int arr[n]; enter large size like 1000000 or more error: segementation fault (core dumped)

    //dynamically allocated array
    int *arr = new int[n]; // no segementation fault
    delete []arr;

    //int temp3 = new int(12); error invalid conversion from int* to int

    /*while (true)
    {
        int temp = 10; //memory destroyed after each function call stack
    }*/

    /*while (true)
    {
        int *ptr = new int;
        //delete ptr;   without delete it is very dangerous, without delete it not just an infinite loop it can crash the system
    }*/

    return 0;
}