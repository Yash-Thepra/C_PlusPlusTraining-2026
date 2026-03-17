#include <iostream>

std::pair getPair()
{
    std::pair<int, int> temp;
    temp.first = 1;
    temp.second = 2;
    return temp;
}

int main()
{
    std::pair<int, int> p;
    p.first = 10;
    p.second = 20;
    std::cout << p.first << " " << p.second << "\n";

    //can also get by return 
    p = getPair();
    return 0;
}