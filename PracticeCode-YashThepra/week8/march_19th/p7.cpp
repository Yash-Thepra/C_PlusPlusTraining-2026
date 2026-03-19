#include <vector>
#include <iostream>
#include <algorithm>

int main() 
{
    //std::vector<int> v1(5, 0);
    std::vector<int> v1 = {0, 0, 0, 0, 0}; //initializer list
    for(int i = 0; i < v1./*capacity()*/size(); i++)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n" << v1.size() << "\n";
    std::cout << v1.capacity() << "\n";
    v1.push_back(10);
    std::cout << v1.capacity() << "\n";
    for(int i = 0; i < v1.size(); i++)
    {
        v1[i] = i;
    }
    for(int i = 0; i < v1.size(); i++)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n";
    std::vector<int> v2(v1); //copy 
    std::cout << "\n\n";
    //std::cout << v2[5] << "\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n";
    for(int i = 0; i < v2.capacity(); i++)
    {
        std::cout << v2[i] << " ";
    }
    v2.pop_back();
    //std::cout << v2[5] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n";
    for(int i = 0; i < v2.capacity(); i++)
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n" << v2.capacity() << "\n";
    std::cout << v2[5] << "\n";
    /*
    std::cout << v2[6] << "\n";
    std::cout << v2[9] << "\n";
    */
}
