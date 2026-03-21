#include <iostream>
#include <gtest/gtest.h>

class example : public testing::Test
{
    int len;
    int widt;
public:
    void SetUp()
    {
        len = 10;
        widt = 15;
    }
    int getPerim()
    {
        return 2 * (len + widt);
    }
};

TEST_F(example, getPerimeter)
{
    EXPECT_EQ(getPerim(), 50);
}

