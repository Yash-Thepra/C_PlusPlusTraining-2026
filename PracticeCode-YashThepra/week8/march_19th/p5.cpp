#include <iostream>

template <class T>
class add
{
    T a;
public:
    add(T value) : a (value)
    {
    }
    T getA();
    /*
      {
        return a;
    }*/
};

template <class U>
U add <U> :: getA()
{
    return a;
}

int main()
{
    add <int> myObj (10);
    std::cout << myObj.getA() << "\n";

    int x = 4;
    int &y = x;

    add <int &> myObj2 (y);
    std::cout << myObj2.getA() << "\n";

    //add <void > myObj3 (); -->error
    add <const int> myObj4 (5);
    std::cout << myObj4.getA() << "\n";
    return 0;
};