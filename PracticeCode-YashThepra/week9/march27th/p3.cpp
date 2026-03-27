#include <thread>
#include <mutex>
#include <iostream>

std::mutex m1, m2;

void task() {
    std::lock(m1, m2);  

    std::lock_guard<std::mutex> l1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> l2(m2, std::adopt_lock);

    std::cout << "Safe critical section\n";
}

int main() {
    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();
}