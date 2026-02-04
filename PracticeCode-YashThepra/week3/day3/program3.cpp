#include <iostream>

int main()
{
    int x = 10;
    int y = 11;

    int& temp = x;
    std::cout << x << " " << y << " " << temp << "\n";
    temp = y;
    std::cout << x << " " << y << " " << temp << "\n"; // can't be reseated, but

    int num = 15;
    int *ptr = &y;
    int*& temp2 = ptr;

    std::cout << "\n\naddress: " << ptr << " " << &y << " " << &temp2 << "\n";
    std::cout << "value: " << *ptr << " " << y << " " << *temp2 << "\n";

    std::cout << "\n" << temp2 << "\n";

    temp2 = &num;
    std::cout << "\n\naddress: " << ptr << " " << &y << " " << &temp2 << " " << &num << "\n";
    std::cout << "value: " << *ptr << " " << y << " " << *temp2 << " " << num << "\n";

    std::cout << "\n" << temp2 << "\n";

    std::cout << "\n\n" << ptr << " " << &num << " " << *ptr << " " << num << "\n";
    return 0;
}