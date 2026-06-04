#include <iostream>

class base
{
protected:
    int id = 11;
public:

    base(int value) : id(value) 
    {
        std::cout << "this is base class ctor.\n";
    }
    
    int getId()
    {
        return id;
    }
    ~base()
    {
        std::cout << "this is base class dtor.\n";
    }
};

class child : public base
{
public:
    child(int value) : base(value)
    {
        std::cout << "this is child class ctor.\n";
        id = value;
    }
    ~child()
    {
        std::cout << "this is child class dtor.\n";
    }
};

int main()
{
    //child c(21);
    //base *b = new child(1);
    //delete b;
    return 0;
}
