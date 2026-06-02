#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void a()
{
    m1.lock();
    std::cout << "m1 is locked by a.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m2.lock();
    std::cout << "m2 is locked by a.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m1.unlock();
    std::cout << "m1 is unlocked by a.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m2.unlock();
    std::cout << "m2 is unlocked by a.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

/*
void b()
{
    m1.lock();
    std::cout << "m1 is locked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m2.lock();
    std::cout << "m2 is locked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m1.unlock();
    std::cout << "m1 is unlocked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m2.unlock();
    std::cout << "m2 is unlocked by b..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}*/

void b()
{
    m2.lock();
    std::cout << "m2 is locked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m1.lock();
    std::cout << "m1 is locked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m2.unlock();
    std::cout << "m2 is unlocked by b.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m1.unlock();
    std::cout << "m1 is unlocked by b..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main()
{
    std::thread t1(a);
    std::thread t2(b);
    t1.join();
    t2.join();
    return 0;
}
