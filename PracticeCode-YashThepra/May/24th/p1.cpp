#include <iostream>
#include <thread>

//int count = 0;
int count = 0;
void randm()
{
    for(int i = 0; i <= 2000000; i++)
    {
        count++;
    }
}

int main()
{
    std::thread t1(randm);
    std::thread t2(randm);
    t1.join();
    t2.join();
    std::cout << count << "\n"; //race condtion briefing because there is data inconsistency.
    return 0;
}
