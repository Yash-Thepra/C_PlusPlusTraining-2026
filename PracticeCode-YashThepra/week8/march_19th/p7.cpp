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
    //std::cout << v2.at(6) << "\n"; // out of range error
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n";
    v2.erase(v2.begin() + 2);
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    //v2.erase(v2.begin() + 5); invalid pointer aborted.
    v2.insert(v2.begin() + 2, 10);
    std::cout << "\n\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n";
    std::cout << v2.front() << "\n";
    std::cout << v2.back() << "\n";
    v2.pop_back();
    std::cout << v2.front() << " " << v2.back() << "\n";
    v2.reserve(100);
    std::cout << v2.capacity() << "\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n\n";
    //std::reverse(v2.begin(), v2.begin() + 8);
    //std::reverse(v2.begin(), v2.begin() + 3);
    std::reverse(v2.begin(), v2.end());
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
    std::reverse(v2.begin(), v2.begin() + 2);
    std::cout << "\n\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    } 
    std::reverse(v2.begin(), v2.begin() - 3);
    //std::reverse(v2.begin(), 2); error
    std::cout << "\n\n";
    for(int i = 0; i < v2.size(); i++) 
    {
        std::cout << v2[i] << " ";
    }
}
