#include <iostream>
#include <map>
#include <unordered_map>
#include <iterator>

int main()
{
    std::map<char, int> m1;
    m1.insert({'a', 1});
    m1.emplace('b', 2);
    std::cout << m1['a'] << " " << m1['b'] << "\n";
    std::cout << m1.at('a') << "\n";
    //m1.at('c')--throws exception
    //std::cout << m1['d'] << "\n";
    m1.erase('a');
    m1.erase('e');
    std::cout << m1['a'] << "\n";
    m1.insert({'c', 3});
    m1.insert({'e', 4});
    m1.insert({'h', 0});
    //m1.insert({'d'}, 10);--> wrong very serious error.
    m1.insert({'d', 10});
    /*
    for(auto it: m1)
    {
        std::cout --> syntactically wrong.
    }*/
    /*
      for(auto it = m1.begin(); it != m1.end(); it++)
    {
        std::cout << it->first << ", " << it->second << " ";
    }*/
    /*
    for(const auto &[key_t, value_compare] : m1)
    {
        std::cout << key_t << ", " << value_compare << " ";
    }
    */
    for(auto it: m1)
    {
        std::cout << it.first << ", " << it.second << " ";
    }
    std::cout << "\n";
    return 0;
}
