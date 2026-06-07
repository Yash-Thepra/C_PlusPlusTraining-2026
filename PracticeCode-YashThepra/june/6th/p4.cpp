#include <iostream>
#include <vector>
#include <iterator>

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    //std::istream_iterator<int> it1(std::cin);
    std::ostream_iterator<int> it2(std::cout);
    *it2 = 4;
    //std::cout << *it2 << "\n";
    return 0;
}
