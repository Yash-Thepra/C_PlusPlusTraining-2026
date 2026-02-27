#include <iostream>
 
class A {
    const int a;
    int b;
public:
    //A() {} /*= default;*/
    A(int x, int y): b(x), a(y){std::cout << "executed.\n";}
};
 
int main()
{
    A a(3, 4);
    //if user defined constructor above is called then it is not handled.

    return 0;
}