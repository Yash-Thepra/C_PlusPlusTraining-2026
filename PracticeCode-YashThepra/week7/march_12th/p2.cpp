#include <iostream>
#include <gtest/gtest.h>

TEST(condition, simple)
{
    //ASSERT_TRUE(1 == 3);
    EXPECT_TRUE(1 == 3);
    std::cout << "I am here.\n";
    EXPECT_TRUE(1 == 1);
}