#include <iostream>
#include <set>
#include <unordered_set>

int main()
{
    std::set<int> s;
    s.insert(3);
    s.insert(2);
    s.insert(3);
    s.insert(3);
    s.insert(1);
    s.insert(1);
    s.insert(2);
    s.insert(2);
    for(auto it : s)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    std::unordered_set<int> un;
    un.insert(33);
    un.insert(22);
    un.insert(33);
    un.insert(33);
    un.insert(11);
    un.insert(11);
    un.insert(22);
    un.insert(22);
    for(auto it : un)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    return 0;
}
