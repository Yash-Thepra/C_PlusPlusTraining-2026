#pragma once

#include "matrix.h"

class Input
{
public:
    static Operation getValidChoice();
    static ProgramEnd getValidPreference();
    static double getValidDouble();
    static int getValidInteger();
};
