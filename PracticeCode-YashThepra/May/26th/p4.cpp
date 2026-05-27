#include <iostream>
#include <thread>
#include <mutex>

std::mutex mt;

void task()
{
    mt.lock();
    //mt.lock();
    int count = 0;
    for(int i = 0; i < 2000000; i++)
    {
        count++;
    }
    std::cout << count << "\n";
    mt.unlock(); //--> if ignored then permanent deadlock
    //mt.unlock(); //--> if done twice we may get undefined behaviour
}

int main()
{
    std::thread t1(task);
    std::thread t2(task);

    t1.join();
    t2.join();
    return 0;
}
