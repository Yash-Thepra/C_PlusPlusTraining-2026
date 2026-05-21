#include <iostream>
#include <thread>

void test()
{
    std::cout << "We are testing the code of thread creation.\n";
}

int main()
{
    //test();
    //std::cout << "End of the program.\n";

    std::thread t1(test);
    //t1.join();
    return 0;
}
