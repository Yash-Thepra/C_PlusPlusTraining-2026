#include <iostream>
#include <gtest/gtest.h>

class emp
{
    int id;
public:
    emp(int id)
    {
        this->id = id;
    }
    int getId()
    {
        return id;
    }
};

class fix : public testing::Test
{
public:
    emp *ep;
    static void SetUpTestSuite()
    {
        if (shared_resource_ != NULL)
        {
            shared_resource_ = new int(11);
            std::cout << "Shared resource with value: " << shared_resource_ << " is expensive.\n";
        }
    }
    static void TearDownTestSuite()
    {
        std::cout << "shared resource cleaned.\n";
        delete shared_resource_;
        shared_resource_ = nullptr;
    }
    void SetUp()
    {
        ep = new emp(10);
    }
    void TearDown()
    {
        delete ep;
    }
    static int *shared_resource_;
};

int* fix::shared_resource_ = nullptr;

TEST_F(fix, fixing)
{
    EXPECT_EQ(10, ep->getId());
}