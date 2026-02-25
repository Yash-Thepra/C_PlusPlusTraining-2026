#include <iostream>

class base 
{
public:
    virtual void print() = 0;
    //{
      //  std::cout << "I am pure virtual base.\n"; error: pure specifier on the function definition.
    //}
};

void base::print()
{
    std::cout << "I can have definition.\n";
}
class derived : public base
{
public:
    void print()
    {
        std::cout << "I can help instantiate this class.\n";
    }
};

int main()
{
    //base b;g+
    //base *b = new derived; unless not defines the pure virtual it also can't bne instantiated.
    base *b = new derived;
    b->print();
    b->base::print();
    return 0;
}