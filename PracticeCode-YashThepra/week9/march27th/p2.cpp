#include <iostream>
#include <list>

int main()
{
    std::list<int> l = {2, 4, 2};
    std::list<int> l2 = {3, 5, 6};
    l.merge(l2);//not accurate result if not sorted
    for(auto it : l)
    {
        std::cout << it << " ";
    }
    //l2 is empty after the merge.
    std::cout << "\n";
    std::list<int> l3 = {1, 2, 3};
    std::list<int> l4 = {4, 5, 6};
    l3.merge(l4);
    for(auto it : l3)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    std::cout << l.size() << " " << l2.size() << " " << l3.size() << " " << l4.size() << "\n";
    return 0;
}
