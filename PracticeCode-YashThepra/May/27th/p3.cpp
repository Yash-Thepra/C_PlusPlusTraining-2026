#include <iostream>
#include <thread>
#include <mutex>

std::mutex mt1, mt2;

void threadA()
{
    std::lock_guard<std::mutex> l1(mt1); 
    //l1.unlock();  --> gives error
    std::lock_guard<std::mutex> l2(mt2);
}

void threadB()
{
    std::lock_guard<std::mutex> l1(mt2);
    std::lock_guard<std::mutex> l2(mt1);
}

int main()
{
    std::thread t1(threadA);
    std::thread t2(threadB);
    t1.join();
    t2.join();
    return 0;
}
//circular wait is done. dead lock
