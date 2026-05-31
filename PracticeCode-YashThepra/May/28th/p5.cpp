#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void helper() {
    std::lock_guard<std::mutex> lock(mtx);  // tries to lock mtx AGAIN
    // ...                                  // ← DEADLOCK, thread waits for itself
}

void func() {
    std::lock_guard<std::mutex> lock(mtx);  // locks mtx
    std::cout << "before helper call.\n";
    helper();                               // calls helper which also locks mtx
    std::cout << "after helper call.\n"; //this never execute because helper never exits and permanent deadlock.
}

int main()
{
    std::thread t(func);
    t.join();
    return 0;
}
