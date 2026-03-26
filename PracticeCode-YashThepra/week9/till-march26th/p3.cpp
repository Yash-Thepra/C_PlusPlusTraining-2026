#include <iostream>
#include <thread>

void print(int x) {
    std::cout << "Value: " << x << "\n";
}

int main() {
    std::thread t(print, 10);
    t.join();
}