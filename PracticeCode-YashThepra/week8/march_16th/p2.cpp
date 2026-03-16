#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(MatcherTest, matchingTests)
{
    testing::Matcher<int> isOne = 1;
    testing::Matcher<int> isZero = 0;
    EXPECT_THAT(1, isOne);
    EXPECT_THAT(-1, isZero);
    //EXPECT_EQ(10, 11);
    int x = 9;
    int y = 10;
    EXPECT_TRUE(x > 9);
    EXPECT_TRUE(x > 11 && y < 5);
}