#include <iostream>
#include <set>

int main()
{
    std::set<int> s;
    s.insert({4, 2, 3, 5});
    for(auto it : s)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    auto it = s.lower_bound(3);
    std::cout << *it << "\n";
    auto it2 = s.upper_bound(3);
    std::cout << *it2 << "\n";

    std::set<int, std::greater<int>> s2; //descedning order
    s2.insert({4, 0, 9, 14, 2, 6, 8});
    for(auto it : s2)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    return 0;
}
