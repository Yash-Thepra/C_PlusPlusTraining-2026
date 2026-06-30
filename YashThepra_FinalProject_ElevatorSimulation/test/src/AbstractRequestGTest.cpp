#include <gtest/gtest.h>

#include "AbstractRequest.hpp"

class TestRequest : public AbstractRequest
{
public:
    explicit TestRequest(const RequestConfiguration& configuration)
        : AbstractRequest(configuration)
    {
    }

    bool isExpired() const override
    {
        return false;
    }
};

class AbstractRequestTest : public ::testing::Test
{
protected:
    TestRequest* request;

    void SetUp() override
    {
        request = new TestRequest(
            RequestConfiguration{
                5,
                Direction::Up,
                RequestType::ExternalUp,
                10,
                100
            });
    }

    void TearDown() override
    {
        delete request;
    }
};

TEST_F(
    AbstractRequestTest,
    GivenRequest_WhenGetFloorIsCalled_ThenConfiguredFloorIsReturned)
{
    EXPECT_EQ(request->getFloor(), 5);
}

TEST_F(
    AbstractRequestTest,
    GivenRequest_WhenGetDirectionIsCalled_ThenConfiguredDirectionIsReturned)
{
    EXPECT_EQ(request->getDirection(), Direction::Up);
}

TEST_F(
    AbstractRequestTest,
    GivenRequest_WhenGetPriorityIsCalled_ThenConfiguredPriorityIsReturned)
{
    EXPECT_EQ(request->getPriority(), 10);
}

TEST_F(
    AbstractRequestTest,
    GivenRequest_WhenGetIdIsCalled_ThenConfiguredIdIsReturned)
{
    EXPECT_EQ(request->getId(), 100);
}

TEST_F(
    AbstractRequestTest,
    GivenRequest_WhenGetTypeIsCalled_ThenConfiguredTypeIsReturned)
{
    EXPECT_EQ(request->getType(), RequestType::ExternalUp);
}

TEST_F(
    AbstractRequestTest,
    GivenConcreteRequest_WhenIsExpiredIsCalled_ThenFalseIsReturned)
{
    EXPECT_FALSE(request->isExpired());
}
