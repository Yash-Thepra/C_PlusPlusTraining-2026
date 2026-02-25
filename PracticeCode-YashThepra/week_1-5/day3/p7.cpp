#include <iostream>

class base
{
/*public:*/
    int a;
    int b;
};

class base2
{
    int x;
    int y;
    int z;
public:
    base2(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    base2(int x, int y, int z): /*z(z)*/ base2(x, y)
    {
        //base2(x, y); temp obj or error, can't init. x and y
        this->z = z;
    }
    void show()
    {
        std::cout << x << " " << y << " " << z << "\n";
    }
};
int main()
{
    //base b{10, 11};
    //std::cout << b.a << " " << b.b << "\n"; error if not public.
    base2 b2(10, 11, 12);
    b2.show();
}