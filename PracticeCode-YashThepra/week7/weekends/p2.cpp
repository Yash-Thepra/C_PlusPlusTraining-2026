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
    std::cout << "I am not disabled.\n";
}

TEST(execption0, notThrown0)
{
    int b = 0;
    if (b == 0)
    {
        GTEST_SKIP();
        std::cout << "can't divide by zero!\n";
    }
    EXPECT_NO_THROW(divide0(13, b));
    std::cout << "I am not disabled.\n";
}

TEST(execption0, DISABLED_anyThrown0)
{
    EXPECT_ANY_THROW(divide0(15, 0));
    std::cout << "I am disabled.\n";
}
