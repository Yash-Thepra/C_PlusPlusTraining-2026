#include <iostream>
#include <gtest/gtest.h>

int divide(int a, int b)
{
    try
    {
        if(b == 0)
        {
            throw -3.14;
        }
    }
    catch (double d)
    {
        std::cout << "->Error code thrown: " << d << "\n->Divide by zero error!\n";
        throw;
    }
    if (b != 0)
    {
        return a / b;
    }
}

TEST(exception, msgRead)
{
    EXPECT_THROW(divide(100, 0), double);
}

TEST(exception, notThrown)
{
    EXPECT_NO_THROW(divide(100, 5));
}

TEST(exception, anyThrown)
{
    EXPECT_ANY_THROW(divide(54304, 0));
}