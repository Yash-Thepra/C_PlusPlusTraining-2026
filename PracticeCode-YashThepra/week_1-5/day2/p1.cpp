#include <iostream>

class base
{
public:
    int x;
    base(int val)
    {
        x = val;
        print();
    }
    virtual void print()
    {
        std::cout << "I am base.\n";
    }
};

class derived : public base
{
public:
    derived(int val) : base{val}
    {
        //print();
    }
    void /*int*/ print()
    {
        std::cout << "I am derived.\n";
    }
};

void printt(base& obj)
{
    obj.print();
}
int main()
{
    //base *b = new derived;
    //b->print();

    derived c(10);
    printt(c);
}