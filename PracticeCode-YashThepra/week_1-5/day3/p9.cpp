#include <iostream>

class base
{
public:
    int ht;
    int wt;
    base(int ht, int wt)
    {
        this->ht = ht;
        this->wt = wt;
    }
    base& operator=(const base& other)
    {
        if (this != &other) /**this == other*/
        {
            this->ht = other.ht;
            this->wt = other.wt;
        }
        return *this;
    }
};

/*void*/std::ostream& operator<<(std::ostream& cout, base& b)
{
    cout << "height: " << b.ht << "\n";
    cout << "weight: " << b.wt << "\n";
    return cout;
}
int main()
{
    base b(10, 11);
    base b2(12, 13);
    std::cout << b << b2;
    b2 = b;
    std::cout << "\n";
    std::cout << b << b2;
    std::cout << "\n";
    b.ht = 20;
    b.wt = 21;
    std::cout << b << b2;
    return 0;
}