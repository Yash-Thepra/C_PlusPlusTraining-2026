#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void taskA()
{
    std::lock(m1, m2);
    std::lock_guard<std::mutex> l1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m2, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "taskA.\n";
}

void taskB()
{
    std::lock(m2, m1); //btw order doesn't matter, (m1, m2) also work that's the core benifit of the lock_gurad and std::lock;
    std::lock_guard<std::mutex> l1(m2, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m1, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "taskB.\n";
}

int main()
{
    std::thread t1(taskA);
    std::thread t2(taskB);
    t1.join();
    t2.join();
    return 0;
}
