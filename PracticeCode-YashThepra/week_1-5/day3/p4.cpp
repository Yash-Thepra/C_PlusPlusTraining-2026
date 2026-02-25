#include <iostream>

class base
{
    int x;
public:
    friend void print(base b);
};

void print(base b)
{
    b.x = 10;
    std::cout << b.x << "\n";
}

int main()
{
    base b;
    print(b);
}