#include <iostream>
#include <queue>

class FunctorObject
{
public:
    bool operator()(int arg1, int arg2)
    {
        return arg1 > arg2;
    }
};

int main()
{
    //mannually creating the priority queue for min heap using function objects.
    //give traditional way: std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    std::priority_queue<int, std::vector<int>, FunctorObject> q;
    q.push(4);
    q.push(5);
    q.push(1);
    q.push(0);
    q.push(11);
    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << "\n";
    return 0;
}
