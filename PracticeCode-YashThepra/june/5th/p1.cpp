#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1, v2;
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    std::cout << "v1: ";
    for(int i : v1)
    {
        std::cout << i << " ";
    }
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    std::cout << "\n\nv2: ";
    for(int i : v2)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    v1.swap(v2);
    std::cout << "v1: ";
    for(int i : v1)
    {
        std::cout << i << " ";
    }
        std::cout << "\n\nv2: ";
    for(int i : v2)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
