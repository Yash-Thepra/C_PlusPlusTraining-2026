#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

bool ready = false;

void consumer()
{
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, []{
        return ready;
    });

    std::cout << "Consumer started\n";
}

void producer()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);

        ready = true;
    }
    cv.notify_one();
    std::cout << "producer started.\n";
}

int main()
{
    std::thread t1(consumer);
    std::thread t2(producer);

    t1.join();
    t2.join();
}
