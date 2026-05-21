#include <iostream>
#include <thread>
#include <unistd.h>

void T1()
{
    for(int i = 1; i <= 10; i++)
    {
        sleep(1);
        std::cout << "I am independent light weight process 1: T1" <<std::endl;
    }
}

void T2()
{
    for(int i = 1; i <= 10; i++)
    {
        sleep(1);
        std::cout << "I am independent light weight process 2: T2" << std::endl;
    }
}

int main()
{
    //T1();
    //T2(); 
    //now with the help of the multi-threading we try to achieve parallism

    std::thread t1(T1);
    std::thread t2(T2);

    t1.join();
    t2.join();
    return 0;
}
