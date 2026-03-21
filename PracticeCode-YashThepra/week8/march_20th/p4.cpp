#include <gtest/gtest.h>

int add(int a, int b)
{
    return a + b;
}

class AddTest : public ::testing::TestWithParam<std::pair<int,int>> {
};

TEST_P(AddTest, PositiveNumbers)
{
    auto [a,b] = GetParam();
    EXPECT_GE(add(a,b), a); 
}

INSTANTIATE_TEST_SUITE_P(
    MyTests,
    AddTest,
    ::testing::Values(
        std::make_pair(2,3),
        std::make_pair(10,5),
        std::make_pair(1,1)
    )
);