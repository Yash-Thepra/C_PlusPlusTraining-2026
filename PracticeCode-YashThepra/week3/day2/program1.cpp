#include <iostream>

struct example {
    int x = 10; // can be initialized in C++
    //can define member functions inside struct in C++
    void Print(int change)
    {
        x = change;
        std::cout << x << "\n";
    }
    static int temp;
    void Print2()
    {
        //temp = 0;
        //temp = 0;
        static int count = 0;
        count++;
        //temp++;
        std::cout << count <<  "\n";
    }
}one;

struct empty1 
{

}two;
int main()
{
    one.Print(11);
    for(int i = 0; i < 5; i++)
    {
        one.Print2();
    }
    //one.temp = 10; undefined reference to example::temp
    /*for(int i = 0; i < 5; i++)
    {
        one.temp = 0; we get compile time erro undefined reference to example::temp
        one.temp++;
        std::cout << one.temp << "\n";
    }*/
    
    std::cout << sizeof(two) << "\n";
    return 0;
}