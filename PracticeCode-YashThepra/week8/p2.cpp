#include <vector>
#include <iostream>

int main()
{

    std::vector<int> vect;
    for (int count=0; count < 6; ++count)
    {
        vect.push_back(10 - count);
    }
    
    for (int index=0; index < vect.size(); ++index)
    {
        std::cout << vect[index] << ' ';
    }

    std::cout << '\n';
}