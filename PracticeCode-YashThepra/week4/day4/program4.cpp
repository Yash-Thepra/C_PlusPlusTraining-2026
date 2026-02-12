#include <iostream>

class over
{
public:
    void operator + ()
    {
        for(int i = 0; i < 10; i++)
        {
            std::cout << "operator is overloaded\n";
        }
    }
    void operator + (int x)
    {
        std::cout << "i am now binary.\n";
    }
    int operator () ()
    {
        return 10;
    }
    void operator - (over& obj)
    {
        std::cout << "i am minus.\n";
    }
};
int main()
{
    over out;
    over an, in;
    out + 10;
    +out;
    in - out;
    std::cout << an () << "\n";
    return 0;
}