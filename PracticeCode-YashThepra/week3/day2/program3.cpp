#include <iostream>

int &refr()
{
    int temp = 10;
    return temp;
}

int main()
{
    int temp = 10;

    //double& ref = temp; can't bind
    const int& ref = temp;
    //ref = 43; error assignment of read only reference
    std::cout << temp << " " << ref << "\n";
    temp = 11;
    std::cout << temp << " " << ref << "\n";

    const int temp2 = 15;
    //int& ref2 = temp2;
    const int& ref2 = temp2;
    //ref2 = 20; assignment of read only reference
    //temp2 = 20; error trying to modify read

    //double temp3 = 20;
    //int& ref3 = temp3; no narrwoing converison happened here

    int x = 10;
    int& a = x;
    int y = 11;
    
    std::cout << a << " " << x << "\n";
    a = y;

    std::cout << a << " " << x << "\n";

    std::cout << y << "\n";
    a = 15;
    std::cout  << y << "\n";
    std::cout << x << "\n";

    //int& c = refr();
    //std::cout << c << "\n";

    return 0;
}