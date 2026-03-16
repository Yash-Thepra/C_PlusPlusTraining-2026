#pragma once
#include <string>

namespace Input
{
    void trimInputData(std::string &data);

    int readMenuChoice(int minimum, int maximum);

    std::string readNonEmptyString();

    std::string readValidMobile();

    std::string readValidPassword();
    
    double readValidDouble();
};
