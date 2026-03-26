#include <iostream>
#include <thread>

void task() {
    std::cout << "Thread running\n";
}

int main() 
{
    std::thread t(task);  
    t.join();             
}