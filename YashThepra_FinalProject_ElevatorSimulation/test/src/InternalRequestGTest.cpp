#include <gtest/gtest.h>

#include "Constant.hpp"
#include "InternalRequest.hpp"

class InternalRequestTest : public ::testing::Test
{
};

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenConstructed_ThenDestinationFloorIsStored)
{
    InternalRequest request(
        10,
        5,
        1);

    EXPECT_EQ(request.getFloor(), 5);
}

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenConstructed_ThenDirectionIsNone)
{
    InternalRequest request(
        10,
        5,
        1);

    EXPECT_EQ(request.getDirection(), Direction::None);
}

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenConstructed_ThenRequestTypeIsInternal)
{
    InternalRequest request(
        10,
        5,
        1);

    EXPECT_EQ(request.getType(), RequestType::Internal);
}

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenConstructed_ThenPriorityIsNormalPriority)
{
    InternalRequest request(
        10,
        5,
        1);

    EXPECT_EQ(request.getPriority(), Constant::normalRequestPriority);
}

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenConstructed_ThenRequestIdIsStored)
{
    InternalRequest request(
        15,
        7,
        0);

    EXPECT_EQ(request.getId(), 15);
}

TEST_F(
    InternalRequestTest,
    GivenInternalRequest_WhenIsExpiredIsCalled_ThenFalseIsReturned)
{
    InternalRequest request(
        10,
        5,
        1);

    EXPECT_FALSE(request.isExpired());
}
