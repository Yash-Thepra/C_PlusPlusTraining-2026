#include <iostream>
#include <unordered_set>
#include <set>

int main()
{
    //std::unordered_set<int> s;
    std::set <int> s;
    s.insert(109);
    s.insert(30);
    s.insert(30);
    s.insert(40);
    s.insert(1);

    for (int x : s)
    {
        std::cout << x << "\n";
    }
}