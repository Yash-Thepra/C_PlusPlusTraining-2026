#include <iostream>
#include <map>

int main()
{
    std::map <std::string, int> m;
    m["boss"] = 18;
    m["yasb"] = 22;
    m.insert({"don", 1});
    std::cout << m["boss"] << "\n";
    std::cout << m["dfsdfsadf"] << "\n";
    std::cout << m.size() <<  " " << m.max_size() << "\n";
    return 0;
}
