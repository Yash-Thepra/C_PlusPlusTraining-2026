#include <iostream>

const char temp = '0';
//nt temp2 = 44;
const double temp2 = 5.32;
enum color
{
    ORANGE ,//= temp, //temp2!wrong must be constant value assigned and also required integeral
    WHITE,
    GREEN
};

int main()
{
    std::cout << ORANGE << "\n";
    std::cout << WHITE << "\n";
    std::cout << GREEN << "\n";
    return 0;
}