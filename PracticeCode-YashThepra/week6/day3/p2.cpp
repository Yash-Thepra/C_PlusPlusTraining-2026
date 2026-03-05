#include <iostream>
#include <unistd.h>

int main()
{
    //std::cout << "I am buffered.\n";
    //std::cout << "I am buffered.";
    std::cerr << "I am not buffered.";
    sleep(5);
    return 0;
}

//uncomment one by one to see the difference.