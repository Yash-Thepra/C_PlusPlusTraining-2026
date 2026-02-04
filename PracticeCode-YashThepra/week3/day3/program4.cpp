#include <iostream>

int main()
{
    int x = 10;
    int& ref1 = x;
    int& ref2 = ref1;

    std::cout << x <<  " " << ref1 << " " << ref2 << "\n";

    //int&& ref3 = ref2; compile time error

    std::cout << &x << " " << &ref1 << " " << &ref2 << "\n";//all have same address since reference variables are not objects.
    //not reference to the reference, just the reference to the x because here lvalue evaluates the ref1 as x since it's just an alias.

    std::cout << "\n\n";
    int y = 10;
    const int& temp = y;
    std::cout << temp << " " << y << "\n";std::cout << "\n" << temp << "\n";
    //temp = 11; error 
    y = 11;
    std::cout << temp << " " << y << "\n";
    return 0;
}