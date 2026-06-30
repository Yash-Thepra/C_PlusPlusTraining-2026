#include <gtest/gtest.h>

#include "ExternalRequest.hpp"
#include "LOOKStrategy.hpp"
#include "ElevatorGTest.hpp"

class LOOKStrategyTest : public ::testing::Test
{
protected:
    LOOKStrategy strategy;
    DispatchContext context{};
};

TEST_F(
    LOOKStrategyTest,
    GivenNoElevators_WhenSelectElevatorIsCalled_ThenRuntimeErrorIsThrown)
{
    ExternalRequest request(5, Direction::Up, 1);

    std::vector<Elevator*> elevators;

    EXPECT_THROW(
        strategy.selectElevator(request, elevators, context),
        std::runtime_error);
}

TEST_F(
    LOOKStrategyTest,
    GivenSingleIdleElevator_WhenSelecting_ThenElevatorIsSelected)
{
    TestElevator elevator(0);

    std::vector<Elevator*> elevators{&elevator};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    LOOKStrategyTest,
    GivenTwoIdleElevators_WhenOneIsCloser_ThenCloserElevatorIsSelected)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(1);
    second.setCurrentFloor(6);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(2, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    LOOKStrategyTest,
    GivenMovingUpElevator_WhenRequestIsAhead_ThenMovingElevatorIsPreferred)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(2);
    first.setDirection(Direction::Up);
    first.setState(ElevatorState::MovingUp);

    second.setCurrentFloor(2);
    second.setState(ElevatorState::Idle);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    LOOKStrategyTest,
    GivenMovingDownElevator_WhenRequestIsAhead_ThenMovingElevatorIsPreferred)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(6);
    first.setDirection(Direction::Down);
    first.setState(ElevatorState::MovingDown);

    second.setCurrentFloor(6);
    second.setState(ElevatorState::Idle);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(3, Direction::Down, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    LOOKStrategyTest,
    GivenOutOfServiceElevator_WhenSelecting_ThenElevatorIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::OutOfService);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(4, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    LOOKStrategyTest,
    GivenMaintenanceElevator_WhenSelecting_ThenElevatorIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::Maintenance);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(4, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    LOOKStrategyTest,
    GivenEmergencyStopElevator_WhenSelecting_ThenElevatorIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::EmergencyStop);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(4, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}
