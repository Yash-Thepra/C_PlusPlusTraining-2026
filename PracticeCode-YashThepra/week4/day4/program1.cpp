#include <iostream>

class shape // abstract class
{
    virtual void draw() = 0;
};

class square : public shape
{
public:
    /*void draw()
    {
        std::cout << "this is an square\n";
    }*/
   void draw()
   {
    std::cout << "Should be implemented\n";
   }
};

int main()
{
    //shape s;
    //square s; implementaion of pure virtual function should be in there otherwise derived class also became an abstract class.
    square s;
    s.draw();
    return 0;
}