#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

void doubles(int number)
{
    std::cout << 2 * number << " ";
}

bool isGreaterThanFive(int number)
{
    return number > 5;
}

int main()
{
    std::vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(6);
    for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    std::for_each(v.begin(), v.end(), doubles);
    std::cout << "\n";
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), 2);
    std::cout << *it << "\n";
    it++;
    std::cout << *it << "\n";
    auto it2 = std::find_if(v.begin(), v.end(), isGreaterThanFive);
    std::cout << *it2 << "\n";
    it2++;
    std::cout << *it2 << "\n";
    it2--;
    it2--;
    std::cout << *it2 << "\n";
    //std::count --> counts specific element and std::count_if, works with predicate.
    std::sort(v.begin(), v.end());
    for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    /* for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";*/
    std::rotate(v.begin(), v.end() - 2, v.end()); //right rotation
    for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    v.push_back(2);
    v.push_back(2);
    v.push_back(4);
    v.push_back(4);
    std::sort(v.begin(), v.end());
    for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    auto itr = std::unique(v.begin(), v.end());
    v.erase(itr, v.end());
    for(auto it : v)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
    
    //int vectorSum = std::accumulate(v.begin(), v.end(), 0);
    //int vectorSum = std::accumulate(v.begin(), v.end(), 4);
    int vectorSum = std::accumulate(v.begin(), v.begin() + 3, 0);
    std::cout << vectorSum << "\n";
    return 0;
}
