#include <iostream>
#define VALUE 10.5

void foo(int parameter)
{
    std::cout << "Hello.\n";
}

void foo2(char a)
{
    std::cout << "Hello2.\n";
}

int main()
{
    int x = 0;

    if (x == 0) 
    {
        //int VALUE = 5; #defines can change the scope.
        //std::cout << VALUE << "\n";
    }

    foo(VALUE);
    foo2(VALUE);//nO type checking
    return 0;
}