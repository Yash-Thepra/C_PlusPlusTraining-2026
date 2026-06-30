#include <gtest/gtest.h>

#include "ExternalRequest.hpp"
#include "FCFSStrategy.hpp"
#include "ElevatorGTest.hpp"

class FCFSStrategyTest : public ::testing::Test
{
protected:
    FCFSStrategy strategy;
    DispatchContext context{};
};

TEST_F(
    FCFSStrategyTest,
    GivenNoElevators_WhenSelectElevatorIsCalled_ThenRuntimeErrorIsThrown)
{
    ExternalRequest request(5, Direction::Up, 1);

    std::vector<Elevator*> elevators;

    EXPECT_THROW(
        strategy.selectElevator(request, elevators, context),
        std::runtime_error);
}

TEST_F(
    FCFSStrategyTest,
    GivenSingleIdleElevator_WhenSelectElevatorIsCalled_ThenElevatorIdIsReturned)
{
    TestElevator elevator(0);

    std::vector<Elevator*> elevators{&elevator};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    FCFSStrategyTest,
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
    FCFSStrategyTest,
    GivenTwoIdleElevators_WhenSecondIsCloser_ThenSecondElevatorIsSelected)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(7);
    second.setCurrentFloor(3);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(2, Direction::Down, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    FCFSStrategyTest,
    GivenIdleAndMovingElevator_WhenDistancesAreEqual_ThenIdleElevatorIsSelected)
{
    TestElevator idle(0);
    TestElevator moving(1);

    idle.setCurrentFloor(4);
    moving.setCurrentFloor(4);

    moving.setState(ElevatorState::MovingUp);

    std::vector<Elevator*> elevators{&moving, &idle};

    ExternalRequest request(6, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    FCFSStrategyTest,
    GivenOutOfServiceElevator_WhenSelecting_ThenItIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::OutOfService);

    second.setCurrentFloor(2);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(3, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    FCFSStrategyTest,
    GivenMaintenanceElevator_WhenSelecting_ThenItIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::Maintenance);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    FCFSStrategyTest,
    GivenEmergencyElevator_WhenSelecting_ThenItIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::EmergencyStop);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

