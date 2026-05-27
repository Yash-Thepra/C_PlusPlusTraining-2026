#include <iostream>
#include <thread>

void task(int& x)
{
    std::cout << x;
}

int main()
{
    int value = 10;
    //int& refr = value;

    //std::thread t(task, /*std::ref(value)*/refr);

    std::thread t(task, std::ref(value));
    std::cout << t.joinable() << "\n";
    t.detach();
    std::cout << t.joinable() << "\n";
}
