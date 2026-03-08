#include <iostream>

int main()
{
    try
    {
        throw std::runtime_error("General");
    }
    catch(const std::exception &e)
    {
        std::cout << "the Exception is: " << e.what() << "\n";
    }
    return 0;
}