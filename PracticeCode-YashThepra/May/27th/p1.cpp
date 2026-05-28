#include <iostream>
#include <thread>
#include <mutex>

std::mutex mt;
int counter = 0;

void increment()
{
    std::lock_guard<std::mutex> lock(mt); //locked here.
    counter++;
    //automatic RAII unlock
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    //t1.join();
    t1.detach();
    t2.detach();
    std::cout << counter << "\n";
}
