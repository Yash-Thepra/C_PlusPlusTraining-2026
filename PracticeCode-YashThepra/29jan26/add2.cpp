#include "add2.h"

/*double*/ int add2(int a, int b, int c) //by including the paired header add2.h in add2.cpp when we change the return type in add2.cpp we'll get notified about that type difference.
{
    return a + b + c; // + a + b + c;
}