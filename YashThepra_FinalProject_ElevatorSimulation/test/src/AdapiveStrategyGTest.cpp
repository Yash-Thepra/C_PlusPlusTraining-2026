#include <gtest/gtest.h>

#include "AdaptiveStrategy.hpp"
#include "Constant.hpp"
#include "ExternalRequest.hpp"
#include "ElevatorGTest.hpp"

class AdaptiveStrategyTest : public ::testing::Test
{
protected:
    AdaptiveStrategy strategy{
        Constant::minimumBasementFloor,
        Constant::maximumFloor};

    ExternalRequest request{5, Direction::Up, 1};

    TestElevator elevator0{0};
    TestElevator elevator1{1};

    std::vector<Elevator*> elevators{&elevator0, &elevator1};

    DispatchContext context{};
};

TEST_F(
    AdaptiveStrategyTest,
    GivenNoElevators_WhenSelectElevatorIsCalled_ThenRuntimeErrorIsThrown)
{
    std::vector<Elevator*> empty;

    EXPECT_THROW(
        strategy.selectElevator(request, empty, context),
        std::runtime_error);
}

TEST_F(
    AdaptiveStrategyTest,
    GivenIdleSystemAndSmallQueue_WhenSelecting_ThenFCFSStrategyIsUsed)
{
    context.pendingQueueSize = Constant::fcfsQueueThreshold;
    context.busyElevators    = 0;

    elevator0.setCurrentFloor(1);
    elevator1.setCurrentFloor(7);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    AdaptiveStrategyTest,
    GivenLargeQueue_WhenSelecting_ThenSCANStrategyIsUsed)
{
    context.pendingQueueSize = Constant::scanQueueThreshold;
    context.busyElevators    = 1;

    elevator0.setCurrentFloor(1);
    elevator1.setCurrentFloor(7);

    EXPECT_NO_THROW(
        strategy.selectElevator(request, elevators, context));
}

TEST_F(
    AdaptiveStrategyTest,
    GivenMediumQueue_WhenSelecting_ThenLOOKStrategyIsUsed)
{
    context.pendingQueueSize = Constant::fcfsQueueThreshold + 2;
    context.busyElevators    = 1;

    elevator0.setCurrentFloor(1);
    elevator1.setCurrentFloor(7);

    EXPECT_NO_THROW(
        strategy.selectElevator(request, elevators, context));
}

TEST_F(
    AdaptiveStrategyTest,
    GivenIdleElevator_WhenUsingAdaptiveStrategy_ThenClosestElevatorIsReturned)
{
    context.pendingQueueSize = 0;
    context.busyElevators    = 0;

    elevator0.setCurrentFloor(2);
    elevator1.setCurrentFloor(6);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    AdaptiveStrategyTest,
    GivenOutOfServiceElevator_WhenSelecting_ThenOperationalElevatorIsReturned)
{
    context.pendingQueueSize = 0;
    context.busyElevators    = 0;

    elevator0.setState(ElevatorState::OutOfService);
    elevator1.setCurrentFloor(4);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    AdaptiveStrategyTest,
    GivenMaintenanceElevator_WhenSelecting_ThenOperationalElevatorIsReturned)
{
    context.pendingQueueSize = 0;
    context.busyElevators    = 0;

    elevator0.setState(ElevatorState::Maintenance);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    AdaptiveStrategyTest,
    GivenEmergencyStopElevator_WhenSelecting_ThenOperationalElevatorIsReturned)
{
    context.pendingQueueSize = 0;
    context.busyElevators    = 0;

    elevator0.setState(ElevatorState::EmergencyStop);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}
