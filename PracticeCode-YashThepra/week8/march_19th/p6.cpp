#include <iostream>

template <class T>
class ex
{
    T a;
public:
    ex(T value) : a(value)
    {

    }
    T getIncrementedA()
    {
        std::cout << "I am the normal one.\n";
        return ++a;
    }
};

template <>
class ex <char>
{
    char ch;
public:
    ex(char value) : ch(value)
    {
    }
    char getIncrementedA()
    {
        if (ch >= 'a' && ch <= 'z')
        {
            std::cout << "I am the specialized one.\n";
            ch = ch - 'a' + 'A';
        }
        return ch;
    }
};

int main()
{
    ex<int> obj1 (10);
    std::cout << obj1.getIncrementedA() << "\n";
    ex<char> obj2 ('h');
    std::cout << obj2.getIncrementedA() << "\n";
    return 0;
}