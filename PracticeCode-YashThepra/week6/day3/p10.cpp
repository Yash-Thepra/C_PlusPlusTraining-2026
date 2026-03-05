#include <iostream>

void D()
{
    std::cout << "Start of D.\nD throwing an Exception.\n";
    throw -1;
    std::cout << "I never executes./End of D.\n";
}
void C()
{
    std::cout << "Start of C.\n";
    D();
    std::cout << "End of C.\n";
}
void B()
{
    std::cout << "Start of B.\n";
    try
    {
        C();
    }
    catch(double)
    {
        std::cout << "Exception of type double Catched by B.\n";
    }
    try
    {
    }
    catch(int)
    {
        std::cout << "Exception of type int Catched by B.\n";
    }
}
void A()
{
    std::cout << "Start of A.\n";
    try
    {
        B();
    }
    /*catch(int)
    {
        std::cout << "Exception of type int handled by A.\n";
    }*/
    catch(double)
    {
        std::cout << "Exception of type double handled by A.\n";
    }
}

int main()
{
    std::cout << "Start of main.\n";
    try
    {
        A();
    }
    catch(int)
    {
        std::cout << "Exception of type int handled at main.\n";// this never executes if we uncomment the int handler in the function A.
    }
    std::cout << "End of main.\n";
    return 0;
}