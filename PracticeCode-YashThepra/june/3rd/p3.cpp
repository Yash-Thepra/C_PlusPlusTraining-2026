#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void ex()
{
    std::cout << "locking.\n";
    mtx.lock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "unlocking.\n";
    mtx.unlock();
}

int main()
{
    std::thread t(ex);
    //t.join();
    if (mtx.try_lock())
    {
        std::cout << "acquired\n";

        mtx.unlock();
    }
    else
    {
        std::cout << "busy\n";
    }
    t.join();
    return 0;
}
