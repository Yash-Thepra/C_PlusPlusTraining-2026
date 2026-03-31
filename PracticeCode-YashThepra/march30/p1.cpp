#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> map;
    std::cout << map.size() << "\n";
    for(int i = 0; i < 10; i++)
    {
        map[i] = i + 1;
    }
    std::cout << map.size() << "\n";
    std::cout << map[4] << "\n";
    //std::cout << map[13443343434] << "\n";
    std::cout << map.count(5) << "\n";
    std::cout << map.count(6) << "\n";
    std::cout << map.count(0) << "\n";
    std::cout << map.count(54) << "\n";
    std::cout << map.count(10) << "\n";
    std::cout << map.count(9) << "\n";

    std::cout << map.at(4) << "\n";
    map.emplace(10, 33);
    std::cout << map[10] << "\n";
    return 0;
}
