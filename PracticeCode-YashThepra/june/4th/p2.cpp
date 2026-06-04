#include <iostream>

class shape
{
public:
    virtual void draw()
    {
        std::cout << "generic.\n";
    }
};

class circle
{
public:
    virtual void draw()
    {
        std::cout << "circle.\n";
    }
};

int main()
{
    shape *s = new shape;
    circle *c = (circle *)s;
    c->draw();
    return 0;
}
