#include <deque>
#include <iostream>

int main() {
    std::deque<int> dq = {1, 4, 3};

    dq.push_back(3);
    dq.push_back(4);
    dq.push_front(2);
    dq.push_front(1);

    std::cout << dq.front() << "\n"; 
    std::cout << dq.back()  << "\n"; 
    std::cout << dq[2] << "\n"; 

    dq.pop_front();
    dq.pop_back();
    std::cout << "\n\n";
    std::cout << dq.front() << "\n";
    std::cout << dq.back() << "\n";
}