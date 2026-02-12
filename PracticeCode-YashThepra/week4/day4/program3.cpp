#include <iostream>

class boss
{

public: // construcotr should be public
    int x;
    boss()
    {
        //return 10; returning a value from construcotr error
    }

   /* void boss()
    {
        std::cout << "function not constructor\n"; can't be overloaded
    }*/
   /*int boss(int num)
   {
    return num; treats as constructor
   }*/
};
int main()
{
    boss yash;
    std::cout << yash.x << "\n";
    boss thepra;
    std::cout << yash.x << "\n";
    return 0;
}