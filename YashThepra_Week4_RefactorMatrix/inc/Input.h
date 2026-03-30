#pragma once

enum Operation
{
    ADDITION = 1,
    MULTIPLICATION
};

namespace Input
{
    Operation readValidChoice();

    bool readValidPreference();

    double readValidDouble();
    
    int readValidInteger();
}
