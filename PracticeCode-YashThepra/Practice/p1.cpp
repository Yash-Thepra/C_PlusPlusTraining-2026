#include <iostream>
#include <iterator>

int main()
{
    std::istream_iterator<int> it(std::cin);
    auto a = it;
    it++;
    std::cout << *a << "\n";
    return 0;
}
