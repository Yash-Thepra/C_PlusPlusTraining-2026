#include <iostream>
#include <vector>
#include <array>

int main()
{
    //std::vector<int> v; showing basic(standard) initialising syntax.
    std::array<int, 3> a = {1, 3, 4};
    for(int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    std::cout << a.back() << "\n";
    a.fill(2);
    std::cout << a.back() << "\n";
    a.fill(3);
    std::cout << a.back() << "\n";
    for(int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    for(int i = a.size() - 1; i >= 0; i--)
    {
        std::cout << a[i] << " ";
    }
    //okay, fill replaces all the present elements in all of the indices with the passed argument element.
    return 0;
}
