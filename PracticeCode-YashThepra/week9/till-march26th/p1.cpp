#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v = {1, 3, 2};
    std::sort(v.begin(), v.end());
    v.push_back(4);
    std::cout << v.back() << "\n";
    v.emplace_back(5);
    std::cout << v.back() << "\n";
    return 0;
}