#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

/*
void task()
{
    std::unique_lock<std::mutex> lock(m);
    std::cout << "This is critical Section.\n";
    lock.unlock(); // we can mannually unlock the unqiue lock;

    std::cout << "This is non-Critical Section that's why we unlocked mannually.\n";
}*/

void deferTask()
{
    std::unique_lock<std::mutex> lock(m, std::defer_lock); //only lock obj. created but mutex not locked.
    std::cout << "mutex still unlocked.\n";
    lock.lock();
    std::cout << "mutex now locked mannually.\n";
}

int main()
{
    //std::thread t(task);
    //std::thread t2(task);
    //t.join();
    //t2.join();
    std::thread defered(deferTask);
    defered.join();
    return 0;
}
