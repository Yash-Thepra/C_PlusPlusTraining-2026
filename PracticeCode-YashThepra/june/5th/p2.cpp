#include <iostream>
#include <queue>

int main()
{
    /*
    std::priority_queue<int> p;   max heap, top element = maximum element
    p.push(30);
    p.push(23);
    p.push(44);
    p.push(5);
    p.push(25);
    while(!p.empty())
    {
        std::cout << p.top() << " ";
        p.pop();
    }
    std::cout << "\n";
    */
    std::priority_queue<int, std::vector<int>, std::greater<int>> p; //min heap, top element = minimum element
    p.push(30);
    p.push(23);
    p.push(44);
    p.push(5);
    p.push(25);
    while(!p.empty())
    {
        std::cout << p.top() << " ";
        p.pop();
    }
    std::cout << "\n";
    return 0;
}
