#include <iostream>
#include <thread>

void task()
{
    std::cout << "Hey!\n";
}

int main()
{
    std::thread t(task);
    t.join();
    //t.join(); --> system error
    if (t.joinable())
    {
        t.join();
    }
    return 0;
}
