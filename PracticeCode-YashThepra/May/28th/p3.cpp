#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void taskA()
{
    std::scoped_lock l(m1, m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "TaskA running.\n";
}

void taskB()
{
    std::scoped_lock l(m1, m2); //order is same still doesn't matter.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "TaskB running.\n";
}

int main()
{
    std::thread t1(taskA);
    std::thread t2(taskB);
    t1.join();
    t2.join();
    return 0;
}
