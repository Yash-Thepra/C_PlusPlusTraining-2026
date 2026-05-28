#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

//int flag = 1;
std::mutex mt;

void func()
{
    //mt.lock();
    std::lock_guard<std::mutex> lock(mt);
    throw std::runtime_error("yes"); // here mutex is unlocked 
    //mt.unlock(); 
}

int main()
{
    std::thread t1(func);
    t1.join();
    return 0;
}
