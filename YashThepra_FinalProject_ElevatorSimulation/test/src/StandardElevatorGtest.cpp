#include <gtest/gtest.h>

#include "ExternalRequest.hpp"
#include "InternalRequest.hpp"
#include "ElevatorGTest.hpp"

class StandardElevatorTest : public ::testing::Test
{
protected:
    TestElevator elevator{
        0,
        Constant::minimumBasementFloor,
        Constant::maximumFloor};
};

TEST_F(
    StandardElevatorTest,
    GivenValidConstructor_WhenCreated_ThenElevatorIdIsInitialized)
{
    EXPECT_EQ(elevator.getId(), 0);
}

TEST_F(
    StandardElevatorTest,
    GivenValidConstructor_WhenCreated_ThenInitialFloorIsGroundFloor)
{
    EXPECT_EQ(
        elevator.getCurrentFloor(),
        Constant::groundFloor);
}

TEST_F(
    StandardElevatorTest,
    GivenValidConstructor_WhenCreated_ThenInitialDirectionIsNone)
{
    EXPECT_EQ(
        elevator.getDirection(),
        Direction::None);
}

TEST_F(
    StandardElevatorTest,
    GivenValidConstructor_WhenCreated_ThenInitialStateIsIdle)
{
    EXPECT_EQ(
        elevator.getState(),
        ElevatorState::Idle);
}

TEST_F(
    StandardElevatorTest,
    GivenInvalidFloorRange_WhenConstructed_ThenExceptionIsThrown)
{
    EXPECT_THROW(
        TestElevator(
            0,
            5,
            5),
        std::invalid_argument);
}

TEST_F(
    StandardElevatorTest,
    GivenCurrentFloor_WhenEstimateArrivalCalled_ThenDistanceIsReturned)
{
    elevator.setCurrentFloor(2);

    EXPECT_EQ(
        elevator.estimateArrival(7),
        5);
}

TEST_F(
    StandardElevatorTest,
    GivenTargetIsCurrentFloor_WhenEstimateArrivalCalled_ThenZeroIsReturned)
{
    elevator.setCurrentFloor(4);

    EXPECT_EQ(
        elevator.estimateArrival(4),
        0);
}

TEST_F(
    StandardElevatorTest,
    GivenElevatorNotRunning_WhenStartCalled_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        elevator.start());

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenRunningElevator_WhenStopCalled_ThenNoExceptionIsThrown)
{
    elevator.start();

    EXPECT_NO_THROW(
        elevator.stop());
}

TEST_F(
    StandardElevatorTest,
    GivenStoppedElevator_WhenStopCalledAgain_ThenNoExceptionIsThrown)
{
    elevator.stop();

    EXPECT_NO_THROW(
        elevator.stop());
}

TEST_F(
    StandardElevatorTest,
    GivenIdleElevator_WhenResumeServiceCalled_ThenStateBecomesIdle)
{
    elevator.resumeService();

    EXPECT_EQ(
        elevator.getState(),
        ElevatorState::Idle);
}

TEST_F(
    StandardElevatorTest,
    GivenIdleElevator_WhenEmergencyTriggered_ThenDirectionBecomesNone)
{
    elevator.start();

    elevator.enterEmergency();

    EXPECT_EQ(
        elevator.getDirection(),
        Direction::None);

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenElevatorAlreadyAtTargetFloor_WhenMoveRequested_ThenFloorRemainsUnchanged)
{
    elevator.setCurrentFloor(4);

    elevator.start();

    EXPECT_EQ(
        elevator.moveToFloor(4),
        4);

    EXPECT_EQ(
        elevator.getCurrentFloor(),
        4);

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenSingleInternalRequest_WhenAdded_ThenQueueFrontMatchesRequest)
{
    elevator.addRequest(
        std::make_unique<InternalRequest>(
            1,
            5,
            0));

    ASSERT_TRUE(
        elevator.getRequestQueueFront().has_value());

    EXPECT_EQ(
        elevator.getRequestQueueFront()->first,
        5);
}

TEST_F(
    StandardElevatorTest,
    GivenSingleExternalRequest_WhenAdded_ThenQueueFrontMatchesRequest)
{
    elevator.addRequest(
        std::make_unique<ExternalRequest>(
            2,
            Direction::Up,
            1));

    ASSERT_TRUE(
        elevator.getRequestQueueFront().has_value());

    EXPECT_EQ(
        elevator.getRequestQueueFront()->first,
        2);

    EXPECT_EQ(
        elevator.getRequestQueueFront()->second,
        Direction::Up);
}

TEST_F(
    StandardElevatorTest,
    GivenEmptyQueue_WhenRequestQueueFrontRequested_ThenNulloptIsReturned)
{
    EXPECT_FALSE(
        elevator.getRequestQueueFront().has_value());
}

TEST_F(
    StandardElevatorTest,
    GivenMultipleRequests_WhenSorted_ThenNearestRequestComesFirst)
{
    elevator.setCurrentFloor(0);

    elevator.addRequest(
        std::make_unique<InternalRequest>(
            1,
            7,
            0));

    elevator.addRequest(
        std::make_unique<InternalRequest>(
            2,
            2,
            0));

    ASSERT_TRUE(
        elevator.getRequestQueueFront().has_value());

    EXPECT_EQ(
        elevator.getRequestQueueFront()->first,
        2);
}

TEST_F(
    StandardElevatorTest,
    GivenEmergencyState_WhenResumeServiceCalled_ThenStateReturnsToIdle)
{
    elevator.start();

    elevator.enterEmergency();

    elevator.resumeService();

    EXPECT_EQ(
        elevator.getState(),
        ElevatorState::Idle);

    EXPECT_EQ(
        elevator.getDirection(),
        Direction::None);

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenDoorClosedState_WhenObstructDoorCalled_ThenOperationFails)
{
    EXPECT_FALSE(
        elevator.obstructDoor());
}

TEST_F(
    StandardElevatorTest,
    GivenDoorNotObstructed_WhenClearObstructionCalled_ThenOperationFails)
{
    EXPECT_FALSE(
        elevator.clearObstruction());
}

class TestObserver : public IObserver
{
public:
    void onFloorArrival(const int elevatorId,
                        const int floor) override
    {
        arrived      = true;
        lastElevator = elevatorId;
        lastFloor    = floor;
    }

    void onRequestServiced(const int elevatorId,
                           const int floor) override
    {
        serviced     = true;
        lastElevator = elevatorId;
        lastFloor    = floor;
    }

    void onStateChanged(const int elevatorId,
                        const ElevatorState state) override
    {
        stateChanged = true;
        lastElevator = elevatorId;
        lastState    = state;
    }

    bool arrived      = false;
    bool serviced     = false;
    bool stateChanged = false;

    int lastElevator = -1;
    int lastFloor    = -1;

    ElevatorState lastState = ElevatorState::Idle;
};

TEST_F(
    StandardElevatorTest,
    GivenRegisteredObserver_WhenFloorArrivalNotified_ThenObserverReceivesNotification)
{
    TestObserver observer;

    elevator.addObserver(&observer);

    elevator.notifyFloorArrival(4);

    EXPECT_TRUE(observer.arrived);
    EXPECT_EQ(observer.lastElevator, 0);
    EXPECT_EQ(observer.lastFloor, 4);
}

TEST_F(
    StandardElevatorTest,
    GivenRegisteredObserver_WhenRequestServicedNotified_ThenObserverReceivesNotification)
{
    TestObserver observer;

    elevator.addObserver(&observer);

    elevator.notifyRequestServiced(6);

    EXPECT_TRUE(observer.serviced);
    EXPECT_EQ(observer.lastElevator, 0);
    EXPECT_EQ(observer.lastFloor, 6);
}

TEST_F(
    StandardElevatorTest,
    GivenRegisteredObserver_WhenStateChanges_ThenObserverReceivesNotification)
{
    TestObserver observer;

    elevator.addObserver(&observer);

    elevator.notifyStateChanged(ElevatorState::MovingUp);

    EXPECT_TRUE(observer.stateChanged);
    EXPECT_EQ(observer.lastElevator, 0);
    EXPECT_EQ(observer.lastState, ElevatorState::MovingUp);
}

TEST_F(
    StandardElevatorTest,
    GivenNullObserver_WhenAdded_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        elevator.addObserver(nullptr));
}

TEST_F(
    StandardElevatorTest,
    GivenStartedElevator_WhenEmergencyTriggered_ThenDirectionBecomesNone)
{
    elevator.start();

    elevator.enterEmergency();

    EXPECT_EQ(
        elevator.getDirection(),
        Direction::None);

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenEmergencyState_WhenResumeServiceCalled_ThenDirectionRemainsNone)
{
    elevator.start();

    elevator.enterEmergency();

    elevator.resumeService();

    EXPECT_EQ(
        elevator.getDirection(),
        Direction::None);

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenNoRequest_WhenServeRequestCalled_ThenNoExceptionIsThrown)
{
    EXPECT_NO_THROW(
        elevator.serveRequest());
}

TEST_F(
    StandardElevatorTest,
    GivenGroundFloor_WhenEmergencyDescendCalled_ThenDoorOpens)
{
    elevator.start();

    EXPECT_NO_THROW(
        elevator.emergencyDescend());

    elevator.stop();
}

TEST_F(
    StandardElevatorTest,
    GivenMultipleObservers_WhenStateChanges_ThenAllObserversReceiveNotification)
{
    TestObserver first;
    TestObserver second;

    elevator.addObserver(&first);
    elevator.addObserver(&second);

    elevator.notifyStateChanged(ElevatorState::DoorOpen);

    EXPECT_TRUE(first.stateChanged);
    EXPECT_TRUE(second.stateChanged);

    EXPECT_EQ(first.lastState, ElevatorState::DoorOpen);
    EXPECT_EQ(second.lastState, ElevatorState::DoorOpen);
}

TEST_F(
    StandardElevatorTest,
    GivenObserverRegistered_WhenMultipleEventsOccur_ThenAllEventsAreDelivered)
{
    TestObserver observer;

    elevator.addObserver(&observer);

    elevator.notifyFloorArrival(2);
    elevator.notifyRequestServiced(2);
    elevator.notifyStateChanged(ElevatorState::Idle);

    EXPECT_TRUE(observer.arrived);
    EXPECT_TRUE(observer.serviced);
    EXPECT_TRUE(observer.stateChanged);

    EXPECT_EQ(observer.lastFloor, 2);
    EXPECT_EQ(observer.lastState, ElevatorState::Idle);
}
