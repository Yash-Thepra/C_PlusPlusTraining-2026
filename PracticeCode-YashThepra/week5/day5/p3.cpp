#include <iostream>

class B
{
public:
    int x;
    B(int val)
    {
        x = val;
    }
    B(B &) = delete;

    B &operator= (B &) = delete;
};

int main()
{
    B b(10);
    //B c(b); 
    //B c = b; error use of deleted function.
    return 0;
}