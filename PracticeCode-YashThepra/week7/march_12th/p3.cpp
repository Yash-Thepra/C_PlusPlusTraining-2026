#include <iostream>
#include <gtest/gtest.h>

//more then 1 test

TEST(Opr, increment)
{
    int value = 100;
    value += 10;

    ASSERT_EQ(value, 110);
}

TEST(Opr, decrement)
{
    int value = 100;
    value -= 10;
    ASSERT_EQ(value, 100);
}