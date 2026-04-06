#include <iostream>
#include <unordered_set>

int main()
{
    // std::unordered_set<int, int> s;
    std::unordered_set<int> s;
    s.insert({4, 3}); // it inserts 4 and 3 both 
    //s.insert(20);
    std::cout << s.size() << "\n";
    //std::cout << s.max_size() << "\n";
    std::cout << s.bucket_size(1) << "\n";
    std::cout << s.bucket_count() << "\n";
    std::cout << s.bucket_size(0) << "\n";
    //s.emplace(3, 2);
    std::cout << "\n";
    for(auto it : s)
    {
        std::cout << it << " ";
    }
    s.insert(4);
    std::cout << "\n";
    return 0;
}
