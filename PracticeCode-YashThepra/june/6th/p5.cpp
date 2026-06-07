#include <vector>
#include <iostream>
#include <algorithm>

class CustomComperator
{
public:
    bool operator () (int a, int b)
    {
        return a > b;
    }
};

int main()
{
    std::vector<int> v;
    v.push_back(4);
    v.push_back(5);
    v.push_back(7);
    v.push_back(1);
    v.push_back(10);
    std::sort(v.begin(), v.end());
    for(auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    //CustomComperator cmp;
    //cmp(3, 3);
    CustomComperator cmp;

    std::sort(v.begin(), v.end(), CustomComperator());
    for(auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
