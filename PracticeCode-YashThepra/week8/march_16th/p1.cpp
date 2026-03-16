#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

class example : public testing::TestWithParam<std::vector<int>>
{};

TEST_P(example, testingexample)
{
    auto in = GetParam();
    auto expected = in;
    std::sort(in.begin(), in.end());
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(expected, in);
}

INSTANTIATE_TEST_SUITE_P(
    sortDifferentInputs, example, 
    testing::Values(
        std::vector<int>{}, 
        std::vector<int> {0}, 
        std::vector<int> {1, 2, 0},
        std::vector<int> {-3, 0, 9},
        std::vector<int> {5, 4, 3, 2, 1}
    )
);