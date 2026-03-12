#include <iostream>
#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

TEST(operation, addition)
{
    //EXPECT_EQ(add(10, 11), 22);
    ASSERT_EQ(add(10, 11), 22);
    std::cout << "I am here.\n";
    EXPECT_EQ(add(10, 12), 22);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}