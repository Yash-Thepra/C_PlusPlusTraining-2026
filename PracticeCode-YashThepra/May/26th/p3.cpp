#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> flag = false;
void task()
{
    int count = 0;
    for(int i = 0; i <= 10000; i++)
    {
        count++;
    }
    std::cout << count << "\n";
    flag = true;
}

int main()
{
    std::thread t(task);
    t.detach();

    if (!flag)
    {
        std::this_thread::yield();
    }
}