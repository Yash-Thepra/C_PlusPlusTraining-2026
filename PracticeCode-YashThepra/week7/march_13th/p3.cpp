#include <iostream>
#include <gtest/gtest.h>

int divide0(int a, int b)
{
    if (b == 0)
    {
        throw 3.14;
    }
    else 
    {
        return a / b;
    }
}

TEST(execption0, isThrown0)
{
    EXPECT_THROW(divide0(10, 0), double);
}

TEST(execption0, notThrown0)
{
    EXPECT_NO_THROW(divide0(13, 5));
}

TEST(execption0, anyThrown0)
{
    EXPECT_ANY_THROW(divide0(15, 0));
}
