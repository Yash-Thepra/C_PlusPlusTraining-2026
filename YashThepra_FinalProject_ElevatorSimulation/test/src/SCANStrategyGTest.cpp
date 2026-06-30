#include <gtest/gtest.h>

#include "ExternalRequest.hpp"
#include "SCANStrategy.hpp"
#include "ElevatorGTest.hpp"

class SCANStrategyTest : public ::testing::Test
{
protected:
    SCANStrategy strategy{
        Constant::minimumBasementFloor,
        Constant::maximumFloor};

    DispatchContext context{};
};

TEST_F(
    SCANStrategyTest,
    GivenNoElevators_WhenSelectElevatorIsCalled_ThenRuntimeErrorIsThrown)
{
    ExternalRequest request(5, Direction::Up, 1);

    std::vector<Elevator*> elevators;

    EXPECT_THROW(
        strategy.selectElevator(request, elevators, context),
        std::runtime_error);
}

TEST_F(
    SCANStrategyTest,
    GivenSingleIdleElevator_WhenSelectElevatorIsCalled_ThenElevatorIsSelected)
{
    TestElevator elevator(0);

    std::vector<Elevator*> elevators{&elevator};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    SCANStrategyTest,
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
    SCANStrategyTest,
    GivenMovingUpElevator_WhenRequestIsAhead_ThenMovingElevatorIsPreferred)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(2);
    first.setDirection(Direction::Up);
    first.setState(ElevatorState::MovingUp);

    second.setCurrentFloor(2);
    second.setDirection(Direction::Down);
    second.setState(ElevatorState::MovingDown);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(5, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    SCANStrategyTest,
    GivenMovingDownElevator_WhenRequestIsAhead_ThenMovingElevatorIsPreferred)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setCurrentFloor(5);
    first.setDirection(Direction::Down);
    first.setState(ElevatorState::MovingDown);

    second.setCurrentFloor(5);
    second.setDirection(Direction::Up);
    second.setState(ElevatorState::MovingUp);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(2, Direction::Down, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        0);
}

TEST_F(
    SCANStrategyTest,
    GivenOutOfServiceElevator_WhenSelecting_ThenElevatorIsIgnored)
{
    TestElevator first(0);
    TestElevator second(1);

    first.setState(ElevatorState::OutOfService);
    second.setCurrentFloor(3);

    std::vector<Elevator*> elevators{&first, &second};

    ExternalRequest request(4, Direction::Up, 1);

    EXPECT_EQ(
        strategy.selectElevator(request, elevators, context),
        1);
}

TEST_F(
    SCANStrategyTest,
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
    SCANStrategyTest,
    GivenEmergencyElevator_WhenSelecting_ThenElevatorIsIgnored)
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
