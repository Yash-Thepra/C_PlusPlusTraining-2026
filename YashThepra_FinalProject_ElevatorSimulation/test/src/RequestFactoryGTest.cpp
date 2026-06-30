#include <gtest/gtest.h>

#include <memory>

#include "ExternalRequest.hpp"
#include "InternalRequest.hpp"
#include "RequestFactory.hpp"

class RequestFactoryTest : public ::testing::Test
{
};

TEST_F(
    RequestFactoryTest,
    GivenValidExternalRequest_WhenCreateExternalIsCalled_ThenExternalRequestIsCreated)
{
    auto request =
        RequestFactory::createExternal(
            5,
            Direction::Up);

    ASSERT_NE(request, nullptr);

    EXPECT_EQ(request->getFloor(), 5);
    EXPECT_EQ(request->getDirection(), Direction::Up);
    EXPECT_EQ(request->getType(), RequestType::ExternalUp);
}

TEST_F(
    RequestFactoryTest,
    GivenValidInternalRequest_WhenCreateInternalIsCalled_ThenInternalRequestIsCreated)
{
    auto request =
        RequestFactory::createInternal(
            1,
            6);

    ASSERT_NE(request, nullptr);

    EXPECT_EQ(request->getFloor(), 6);
    EXPECT_EQ(request->getDirection(), Direction::None);
    EXPECT_EQ(request->getType(), RequestType::Internal);
}

TEST_F(
    RequestFactoryTest,
    GivenFloorBelowMinimum_WhenCreateExternalIsCalled_ThenOutOfRangeExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createExternal(
            Constant::minimumBasementFloor - 1,
            Direction::Up),
        std::out_of_range);
}

TEST_F(
    RequestFactoryTest,
    GivenFloorAboveMaximum_WhenCreateExternalIsCalled_ThenOutOfRangeExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createExternal(
            Constant::maximumFloor + 1,
            Direction::Up),
        std::out_of_range);
}

TEST_F(
    RequestFactoryTest,
    GivenDirectionNone_WhenCreateExternalIsCalled_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createExternal(
            3,
            Direction::None),
        std::invalid_argument);
}

TEST_F(
    RequestFactoryTest,
    GivenNegativeElevatorId_WhenCreateInternalIsCalled_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createInternal(
            -1,
            3),
        std::invalid_argument);
}

TEST_F(
    RequestFactoryTest,
    GivenElevatorIdGreaterThanMaximum_WhenCreateInternalIsCalled_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createInternal(
            Constant::totalElevators,
            3),
        std::invalid_argument);
}

TEST_F(
    RequestFactoryTest,
    GivenFloorBelowMinimum_WhenCreateInternalIsCalled_ThenOutOfRangeExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createInternal(
            0,
            Constant::minimumBasementFloor - 1),
        std::out_of_range);
}

TEST_F(
    RequestFactoryTest,
    GivenFloorAboveMaximum_WhenCreateInternalIsCalled_ThenOutOfRangeExceptionIsThrown)
{
    EXPECT_THROW(
        RequestFactory::createInternal(
            0,
            Constant::maximumFloor + 1),
        std::out_of_range);
}

TEST_F(
    RequestFactoryTest,
    GivenMultipleRequests_WhenCreated_ThenRequestIdsAreUnique)
{
    auto first =
        RequestFactory::createExternal(
            1,
            Direction::Up);

    auto second =
        RequestFactory::createExternal(
            2,
            Direction::Down);

    EXPECT_NE(first->getId(), second->getId());
}
