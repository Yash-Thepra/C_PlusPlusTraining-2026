#include <iostream>

class ex
{
private:

public:
    int x = 10;
    /*const*/ int &getX() //const
    {
        return x;
    }
};

int main()
{
    ex e;
    //int temp = e.getX();
    int &temp = e.getX();
    std::cout << temp << "\n";
    temp = 11;//modifies object values
    std::cout << e.x << "\n";
    return 0;
}