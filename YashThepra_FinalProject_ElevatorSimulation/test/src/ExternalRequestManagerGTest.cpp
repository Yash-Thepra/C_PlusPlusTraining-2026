#include <gtest/gtest.h>

#include "ExternalRequest.hpp"
#include "ExternalRequestManager.hpp"

class ExternalRequestManagerTest : public ::testing::Test
{
protected:
    ExternalRequestManager manager;
};

TEST_F(
    ExternalRequestManagerTest,
    GivenNewRequest_WhenSubmitted_ThenSubmissionSucceeds)
{
    ExternalRequest request(
        3,
        Direction::Up,
        1);

    EXPECT_TRUE(manager.submitRequest(request));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenDuplicateRequest_WhenSubmitted_ThenSubmissionFails)
{
    ExternalRequest request(
        3,
        Direction::Up,
        1);

    EXPECT_TRUE(manager.submitRequest(request));
    EXPECT_FALSE(manager.submitRequest(request));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenRequestServiced_WhenSameRequestSubmittedAgain_ThenSubmissionSucceeds)
{
    ExternalRequest request(
        3,
        Direction::Up,
        1);

    EXPECT_TRUE(manager.submitRequest(request));

    manager.onRequestServiced(
        3,
        Direction::Up);

    EXPECT_TRUE(manager.submitRequest(request));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenRequestsFromDifferentFloors_WhenSubmitted_ThenAllSucceed)
{
    ExternalRequest first(
        2,
        Direction::Up,
        1);

    ExternalRequest second(
        5,
        Direction::Up,
        2);

    EXPECT_TRUE(manager.submitRequest(first));
    EXPECT_TRUE(manager.submitRequest(second));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenRequestsWithDifferentDirections_WhenSubmitted_ThenBothSucceed)
{
    ExternalRequest up(
        4,
        Direction::Up,
        1);

    ExternalRequest down(
        4,
        Direction::Down,
        2);

    EXPECT_TRUE(manager.submitRequest(up));
    EXPECT_TRUE(manager.submitRequest(down));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenRequestAlreadyQueued_WhenDifferentRequestIdIsSubmitted_ThenSubmissionFails)
{
    ExternalRequest first(
        6,
        Direction::Down,
        1);

    ExternalRequest second(
        6,
        Direction::Down,
        99);

    EXPECT_TRUE(manager.submitRequest(first));
    EXPECT_FALSE(manager.submitRequest(second));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenServicedUpRequest_WhenDownRequestExists_ThenDownRequestRemainsBlocked)
{
    ExternalRequest up(
        5,
        Direction::Up,
        1);

    ExternalRequest down(
        5,
        Direction::Down,
        2);

    EXPECT_TRUE(manager.submitRequest(up));
    EXPECT_TRUE(manager.submitRequest(down));

    manager.onRequestServiced(
        5,
        Direction::Up);

    EXPECT_TRUE(manager.submitRequest(up));
    EXPECT_FALSE(manager.submitRequest(down));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenMultipleServiceOperations_WhenRepeated_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        manager.onRequestServiced(
            2,
            Direction::Up));

    EXPECT_NO_THROW(
        manager.onRequestServiced(
            2,
            Direction::Up));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenDifferentFloorSameDirection_WhenSubmitted_ThenBothRequestsAreAccepted)
{
    ExternalRequest first(
        1,
        Direction::Up,
        1);

    ExternalRequest second(
        2,
        Direction::Up,
        2);

    EXPECT_TRUE(manager.submitRequest(first));
    EXPECT_TRUE(manager.submitRequest(second));
}

TEST_F(
    ExternalRequestManagerTest,
    GivenDifferentFloorDifferentDirection_WhenSubmitted_ThenAllRequestsAreAccepted)
{
    ExternalRequest first(
        1,
        Direction::Up,
        1);

    ExternalRequest second(
        2,
        Direction::Down,
        2);

    EXPECT_TRUE(manager.submitRequest(first));
    EXPECT_TRUE(manager.submitRequest(second));
}
