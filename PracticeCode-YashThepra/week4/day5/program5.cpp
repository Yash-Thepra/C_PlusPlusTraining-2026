#include <iostream>

class ex
{
public:
    void print()
    {
        std::cout << "I can modify.\n";
    }
    void print() const 
    {
        std::cout << "I am constant.\n";
    }
};

int main()
{
    ex x;
    x.print();

    const ex y;
    y.print();
    return 0;
}