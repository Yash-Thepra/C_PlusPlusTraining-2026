#include <iostream>
#include <gtest/gtest.h>

void Exit(int code = 0)
{
    std::cout << "Exiting with the code: " << code << " ";
    std::exit(code);
}

TEST(myDeathTest, death)
{
    //EXPECT_DEATH(exit(10), "");
    //EXPECT_DEATH(Exit(0), "");
    EXPECT_DEATH(Exit(1), "");
    std::cout << "I am still able to continue.\n";
}

TEST(myDeathTest, normalExit)
{
    EXPECT_EXIT(Exit(0), testing::ExitedWithCode(0), "");
}

TEST(myDeathTest, abnormalExit)
{
    EXPECT_EXIT(Exit(1), testing::ExitedWithCode(1), "");
}
