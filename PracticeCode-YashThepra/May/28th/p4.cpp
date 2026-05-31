#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void a()
{
    std::lock_guard<std::mutex> l1(m1);
    std::lock_guard<std::mutex> l2(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "a running.\n";
}

void b()
{
    std::lock_guard<std::mutex> l1(m1);
    std::lock_guard<std::mutex> l2(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "b running.\n";
}

int main()
{
    std::thread t1(a);
    std::thread t2(b);
    t1.join();
    t2.join();
    return 0;
}
