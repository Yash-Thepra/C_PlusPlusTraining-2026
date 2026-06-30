#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ElevatorScheduler.hpp"
#include "ExternalRequest.hpp"
#include "DispatchStrategyGMock.hpp"
#include "ElevatorGTest.hpp"

using ::testing::_;
using ::testing::Return;

class ElevatorSchedulerTest : public ::testing::Test
{
protected:
    ElevatorScheduler& scheduler = ElevatorScheduler::getInstance();

    TestElevator elevator0{0};
    TestElevator elevator1{1};

    void SetUp() override
    {
        scheduler.stopScheduler();

        scheduler.registerElevator(&elevator0);
        scheduler.registerElevator(&elevator1);
    }

    void TearDown() override
    {
        scheduler.stopScheduler();
    }
};

TEST_F(
    ElevatorSchedulerTest,
    GivenScheduler_WhenGetStrategyCalled_ThenStrategyIsNotNull)
{
    EXPECT_NE(
        scheduler.getStrategy(),
        nullptr);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenScheduler_WhenPendingQueueIsEmpty_ThenPendingCountIsZero)
{
    EXPECT_EQ(
        scheduler.getPendingCount(),
        0);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenNullStrategy_WhenSetStrategyCalled_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        scheduler.setStrategy(nullptr),
        std::invalid_argument);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenValidMockStrategy_WhenSetStrategyCalled_ThenStrategyIsUpdated)
{
    auto strategy = std::make_unique<DispatchStrategyGMock>();

    DispatchStrategyGMock* raw = strategy.get();

    scheduler.setStrategy(std::move(strategy));

    EXPECT_EQ(
        scheduler.getStrategy(),
        raw);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenRegisteredElevator_WhenRegisterElevatorCalledWithNullptr_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        scheduler.registerElevator(nullptr));
}

TEST_F(
    ElevatorSchedulerTest,
    GivenMockStrategy_WhenScheduleCalled_ThenStrategySelectElevatorIsInvoked)
{
    auto strategy = std::make_unique<DispatchStrategyGMock>();

    EXPECT_CALL(
        *strategy,
        selectElevator(_, _, _))
        .Times(1)
        .WillOnce(Return(0));

    scheduler.setStrategy(std::move(strategy));

    ExternalRequest request(
        5,
        Direction::Up,
        1);

    scheduler.schedule(request);

    EXPECT_EQ(
        scheduler.getPendingCount(),
        1);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenEmptyQueue_WhenProcessNextCalled_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        scheduler.processNext());
}

TEST_F(
    ElevatorSchedulerTest,
    GivenScheduler_WhenStartSchedulerCalled_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        scheduler.startScheduler());

    scheduler.stopScheduler();
}

TEST_F(
    ElevatorSchedulerTest,
    GivenRunningScheduler_WhenStartSchedulerCalledAgain_ThenNoExceptionIsThrown)
{
    scheduler.startScheduler();

    EXPECT_NO_THROW(
        scheduler.startScheduler());

    scheduler.stopScheduler();
}

TEST_F(
    ElevatorSchedulerTest,
    GivenStoppedScheduler_WhenStopSchedulerCalledAgain_ThenNoExceptionIsThrown)
{
    scheduler.stopScheduler();

    EXPECT_NO_THROW(
        scheduler.stopScheduler());
}

TEST_F(
    ElevatorSchedulerTest,
    GivenSchedulerLoop_WhenStartedAndStopped_ThenNoExceptionIsThrown)
{
    scheduler.startScheduler();

    std::this_thread::sleep_for(
        std::chrono::milliseconds(20));

    EXPECT_NO_THROW(
        scheduler.stopScheduler());
}

TEST_F(
    ElevatorSchedulerTest,
    GivenMockStrategyReturningSecondElevator_WhenScheduling_ThenRequestIsQueued)
{
    auto strategy = std::make_unique<DispatchStrategyGMock>();

    EXPECT_CALL(
        *strategy,
        selectElevator(_, _, _))
        .WillOnce(Return(1));

    scheduler.setStrategy(std::move(strategy));

    scheduler.schedule(
        ExternalRequest(
            7,
            Direction::Up,
            10));

    EXPECT_EQ(
        scheduler.getPendingCount(),
        1);
}

TEST_F(
    ElevatorSchedulerTest,
    GivenScheduler_WhenGetStrategyCalledMultipleTimes_ThenSamePointerIsReturned)
{
    IDispatchStrategy* first =
        scheduler.getStrategy();

    IDispatchStrategy* second =
        scheduler.getStrategy();

    EXPECT_EQ(
        first,
        second);
}

