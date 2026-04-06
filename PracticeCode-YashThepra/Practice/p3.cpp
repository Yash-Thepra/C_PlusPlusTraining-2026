#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> m;
    m.insert({3, 103});
    m[2] = 102;
    m.emplace(1, 101);
    m[0] = 100;
    m.insert({5, 105});
    m.insert({5, 106}); 
    std::cout << m[5] << "\n";
    //std::cout << m[6] << "\n";
    for(auto it : m)
    {
        std::cout << it.first << ", " << it.second << " ";
    }
    std::cout << "\n";
    /*std::cout << m[1] << "\n";
    m[1];
    std::cout << m[1] << "\n";*/
    return 0;
}
