#pragma once

#include <string>

namespace Input
{
    int readMenuChoice(const int minimum, const int maximum);

    std::string readNonEmptyString();

    void trimInputData(std::string &data);
}
