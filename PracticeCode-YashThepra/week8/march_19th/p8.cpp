#include <iostream>
#include <list>
#include <algorithm>

int main()
{
    std::list <int> lst = {1, 1, 4, 2, 5, 6, 2, 3, 5, 4};
    std::cout << lst.front() << "\n";
    std::cout << lst.back() << "\n";
    std::list <int> lst2(lst);
    lst.push_front(0);
    std::cout << lst.front() << "\n";
    lst.pop_back();
    std::cout << lst.back() << "\n";
    lst.push_back(6);
    std::cout << lst.back() << "\n";
    auto it = std::find(lst.begin(), lst.end(), 3);
    std::cout << *it << "\n";
    lst.insert(it, 9);
    while (it != lst.end())
    {
        std::cout << *it << " ";
        it++;
    }
    auto it = std::find (lst.begin(), lst.end(), 3);
    return 0;
}