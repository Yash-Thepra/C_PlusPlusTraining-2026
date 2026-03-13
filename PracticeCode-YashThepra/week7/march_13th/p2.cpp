#include <iostream>
#include <gtest/gtest.h>

TEST(assertion_macros, floatType)
{
    //EXPECT_FLOAT_EQ(12.1, 12.099999);
    EXPECT_FLOAT_EQ(12.3459, 12.3469);
}

TEST(assertion_macros, doubleType)
{
    EXPECT_DOUBLE_EQ(15000000000, 15000000000.0000001);
}

TEST(abs_diff, diff)
{
    EXPECT_NEAR(10, 16, 7);
}