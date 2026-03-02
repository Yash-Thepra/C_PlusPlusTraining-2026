#include <iostream>

enum boss
{
    faaah,
    bosss,
    yash,
    yes,
};

int main()
{
    int choice;
    std::cin >> choice;
    switch(choice)
    {
        case faaah: std::cout << "Faaahh.\n"; break;
        /*case '\0': */ // --> duplicate case error. compiler may also implement the jump table based on the range and difference and also the numbner of case, and because of the jump table it is more efficient than if-else.
        case bosss: std::cout << "I am the boss.\n"; break;
        case yes: std::cout << "yes boss.\n"; break;
        case 1 + 3: std::cout << "Constant airthmetic can work.\n"; break;
        case faaah + 5: std::cout << "enumumeration or variable airthmetic can also work can also work.\n"; break;
        default: std::cout << "Invalid choice!\n";
    }
    return 0;
}