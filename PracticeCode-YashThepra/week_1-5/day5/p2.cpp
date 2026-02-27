#include <iostream>
 
class A {
    int b;
public:
    A() {}
    A(int x = 10): b(x){}
};
 
int main()
{
    A a(10);
    //A a; --> error
    //A a() --> error
    return 0;
}