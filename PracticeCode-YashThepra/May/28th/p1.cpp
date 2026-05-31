#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void taskA()
{
    m1.lock();
    std::cout << "taskA.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m2.lock();
    std::cout << "out of taskA critical Section.\n";
}

void taskB()
{
    m2.lock();
    std::cout << "taskB.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m1.lock();
    std::cout << "out of taskB critical Section.\n";
}

int main()
{
    std::thread t1(taskA);
    std::thread t2(taskB);
    t1.join();
    t2.join();
    return 0;
} // circular waiting deadlock.
 