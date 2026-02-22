#include <iostream>

class A
{
    static inline int x;
    static A* _instance;
    A()
    {
        std::cout << "instance created.\n";
        x = 10;
    }
    ~A() = default;
public:
    A (const A&) = delete;
    A& operator=(const A&) = delete;
    static A* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new A();
        }
        return _instance;
    }
    void print()
    {
        std::cout << x << "\n";
    }
};
A* A::_instance = NULL;
int main()
{
    A *a = A::getInstance();
    a->print();
    A *b = A::getInstance();
    b->print();
    std::cout << a << " " << b << "\n";// same meaning only single object is created.
    return 0;
}