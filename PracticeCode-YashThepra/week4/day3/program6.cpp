#include <iostream>

class A
{
    public:
    void print()
    {
        std::cout << "A here.\n";
    }
};
class B
{
    public:
    void print()
    {
        std::cout << "B here.\n";
    }
};
class C : public A, public B
{
    private:
    int x = 10;
    public:
    int get() const
    {
        //x++; complie error
        return x;
    }
};
int main()
{
    C c;
    //c.print();ambigous
    c.A::print();
    c.B::print();
    std::cout << c.get() << "\n";

    const C ch;
    //ch.A::print(); const C as this argument discards qualifier
    return 0;
}