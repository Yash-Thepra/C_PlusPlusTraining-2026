#include <iostream>
#include <list>

int main()
{
    std::list <int> l;
    for(int i = 0; i < 10; i++)
    {
        l.push_back(i);
    }
    
   /* for(int j = 0; j < 10; j++)
    {

        std::cout << l.front() << "\n";
        l.pop_front(); 
    }*/
    for(int j = 0; j < 10; j++)
    {

        std::cout << l.back() << "\n";
        l.pop_back();
    }
}