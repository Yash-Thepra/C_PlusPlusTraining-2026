#include <iostream>
#include <thread>

void task()
{
    int count = 1;
    for(int i = 0; i <= 10000; i++)
    {
        count++;
    }
    std::cout << count << "\n";
}

int main()
{
    std::thread t(task);
    t.detach();
    //t.join();
    return 0;
}
