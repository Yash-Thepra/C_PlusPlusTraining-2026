#include <iostream>
#include <map>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> m;
    m.insert(std::make_pair("king", 18));
    m.insert(std::make_pair("thala", 7));
    //m.insert(std::make_pair("thala", 7));
    m.insert(std::make_pair("boss", 1));
    //auto it = m.find("boss");
    //std::cout << it->second << "\n";
    //auto it = m.find("bosss");
    //std::cout << it->first << "\n"; //--> core dumped
    for(auto it : m)
    {
        std::cout << it.first << " " << it.second << "\n";
    }
    std::cout << "\n";
    std::map<std::string, int> m2;
    m2.insert(std::make_pair("king", 18));
    m2.insert(std::make_pair("thala", 7));
    //m2.insert(std::make_pair("thala", 7));
    //m2.insert(std::make_pair("king", 1));
    m2.insert(std::make_pair("boss", 1));
    for(auto it : m2)
    {
        std::cout << it.first << " " << it.second << "\n";
    }
    return 0;
}
