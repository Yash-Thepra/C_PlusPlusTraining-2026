#include <iostream>

template <class T, class U>
auto /*T*/ getMin(T a, U b)
{
    return a > b ? a : b;
}

int main()
{
    int x = 4;
    double y = 5.2;
    std::cout << getMin <int, double> (x, y) << "\n";
    std::cout << getMin(x, y) << "\n";
    std::cout << getMin <int, double> (y, x) << "\n";
    std::cout << getMin <double, int> (y, x) << "\n";
    std::cout << getMin <double> (y, x) << "\n";
    std::cout << getMin <double, double> (y, x) << "\n";
    return 0;
}
