#include <iostream>

void foo()
{

}
int goo()
{
    return 1;
}

void gooo() noexcept
{

}

int main()
{
    std::cout << noexcept(3 + 7) << "\n";
    std::cout << noexcept(foo()) << "\n";
    std::cout << noexcept(goo()) << "\n";
    std::cout << noexcept(gooo()) << "\n";
}