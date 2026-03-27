#include <iostream>

#include "Application.h"

int main()
{
    int returnStatement = 0;
    try
    {
        return runApplication();
    }
    catch (...)
    {
        returnStatement = 1;
        std::cout << "Fatal error occurred\n";
    }
    return returnStatement;
}
