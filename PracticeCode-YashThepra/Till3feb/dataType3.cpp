#include <iostream>

int main()
{
    int number = 3.3;
    std::cout << "number: " << number << "\n";
    number = 'a';
    std::cout << "number: " << number << "\n";
    //number = 'adfds';//garbage value
    //std::cout << "number: " << number << "\n";
    //number = 'as';//garbage value
    //std::cout << "number: " << number << "\n";

    char character = 3;
    std::cout << "character: " << character << "\n";
    std::cout << "character: " << (int)character << "\n";

    character = 'a';
    std::cout << "character: " << character << "\n";
    character = 97;
    std::cout << "character: " << character << "\n";
}
