#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
    int max_count;

public:
    Semaphore(int initial)
        : count(initial),
          max_count(initial)
    {
    }

    void acquire()
    {
        std::unique_lock<std::mutex> lock(mtx);
        //std::lock_guard<std::mutex> lock(mtx);
        cv.wait(lock, [this]
        {
            return count > 0;
        });

        --count;
    }

    void release()
    {
        std::unique_lock<std::mutex> lock(mtx);

        if(count < max_count)
        {
            ++count;
            cv.notify_one();
        }
    }
};

//Semaphore sem(1);
Semaphore sem(3);

void worker(int id)
{
    sem.acquire();

    std::cout << "Thread "
              << id
              << " entered\n";

    std::this_thread::sleep_for(
        std::chrono::seconds(2));

    std::cout << "Thread "
              << id
              << " leaving\n";

    sem.release();
}

int main()
{
    std::vector<std::thread> threads;

    for(int i = 1; i <= 5; i++)
    {
        threads.emplace_back(worker, i);
    }

    for(auto& t : threads)
    {
        t.join();
    }
    return 0;
}
