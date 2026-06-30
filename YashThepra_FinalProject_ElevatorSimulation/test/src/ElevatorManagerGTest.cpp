#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ElevatorManager.hpp"
#include "SchedulerGMock.hpp"
#include "ElevatorGTest.hpp"

using ::testing::_;
using ::testing::Exactly;

class ElevatorManagerTest : public ::testing::Test
{
protected:
    SchedulerGMock scheduler;
    ElevatorManager manager{&scheduler};
};

TEST_F(
    ElevatorManagerTest,
    GivenNullScheduler_WhenConstructed_ThenThrowsInvalidArgument)
{
    EXPECT_THROW(
        ElevatorManager(nullptr),
        std::invalid_argument);
}

TEST_F(
    ElevatorManagerTest,
    GivenNewManager_WhenGetElevatorCountCalled_ThenZeroIsReturned)
{
    EXPECT_EQ(
        manager.getElevatorCount(),
        0);
}

TEST_F(
    ElevatorManagerTest,
    GivenNullElevator_WhenAddElevatorCalled_ThenCountRemainsZero)
{
    manager.addElevator(nullptr);

    EXPECT_EQ(
        manager.getElevatorCount(),
        0);
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenAdded_ThenCountBecomesOne)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_EQ(
        manager.getElevatorCount(),
        1);
}

TEST_F(
    ElevatorManagerTest,
    GivenTwoElevators_WhenAdded_ThenCountBecomesTwo)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(2);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    manager.addElevator(
        std::make_unique<TestElevator>(1));

    EXPECT_EQ(
        manager.getElevatorCount(),
        2);
}

TEST_F(
    ElevatorManagerTest,
    GivenExistingElevator_WhenGetByIdCalled_ThenCorrectPointerReturned)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(7));

    Elevator* elevator =
        manager.getElevatorById(7);

    ASSERT_NE(
        elevator,
        nullptr);

    EXPECT_EQ(
        elevator->getId(),
        7);
}

TEST_F(
    ElevatorManagerTest,
    GivenMissingElevator_WhenGetByIdCalled_ThenNullptrReturned)
{
    EXPECT_EQ(
        manager.getElevatorById(100),
        nullptr);
}

TEST_F(
    ElevatorManagerTest,
    GivenNullObserver_WhenAddedToAll_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.addObserverToAll(nullptr));
}

TEST_F(
    ElevatorManagerTest,
    GivenValidExternalRequest_WhenHandled_ThenSchedulerReceivesRequest)
{
    EXPECT_CALL(
        scheduler,
        schedule(_))
        .Times(1);

    EXPECT_NO_THROW(
        manager.handleExternalRequest(
            Constant::groundFloor,
            Direction::Up));
}

TEST_F(
    ElevatorManagerTest,
    GivenInvalidElevatorId_WhenInternalRequestHandled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.handleInternalRequest(
            99,
            Constant::groundFloor));
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenInternalRequestHandled_ThenNoExceptionThrown)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_NO_THROW(
        manager.handleInternalRequest(
            0,
            5));
}

TEST_F(
    ElevatorManagerTest,
    GivenNoElevators_WhenStartAllCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.startAll());
}

TEST_F(
    ElevatorManagerTest,
    GivenNoElevators_WhenStopAllCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.stopAll());
}

TEST_F(
    ElevatorManagerTest,
    GivenNoElevators_WhenTriggerEmergencyAllCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.triggerEmergencyAll());
}

TEST_F(
    ElevatorManagerTest,
    GivenNoElevators_WhenResumeServiceAllCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.resumeServiceAll());
}

TEST_F(
    ElevatorManagerTest,
    GivenInvalidElevatorId_WhenTriggerEmergencyCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.triggerEmergency(50));
}

TEST_F(
    ElevatorManagerTest,
    GivenInvalidElevatorId_WhenResumeServiceCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.resumeService(50));
}

TEST_F(
    ElevatorManagerTest,
    GivenInvalidElevatorId_WhenObstructDoorCalled_ThenFalseReturned)
{
    EXPECT_FALSE(
        manager.obstructDoor(99));
}

TEST_F(
    ElevatorManagerTest,
    GivenInvalidElevatorId_WhenClearObstructionCalled_ThenFalseReturned)
{
    EXPECT_FALSE(
        manager.clearObstruction(99));
}

TEST_F(
    ElevatorManagerTest,
    GivenObserverCallbacks_WhenInvoked_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        manager.onFloorArrival(
            0,
            Constant::groundFloor));

    EXPECT_NO_THROW(
        manager.onRequestServiced(
            0,
            Constant::groundFloor));

    EXPECT_NO_THROW(
        manager.onStateChanged(
            0,
            ElevatorState::Idle));
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenResumeServiceCalled_ThenNoExceptionThrown)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_NO_THROW(
        manager.resumeService(0));
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenResumeServiceAllCalled_ThenNoExceptionThrown)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_NO_THROW(
        manager.resumeServiceAll());
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenGetElevatorByWrongIdCalled_ThenNullptrReturned)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_EQ(
        manager.getElevatorById(5),
        nullptr);
}

TEST_F(
    ElevatorManagerTest,
    GivenMultipleElevators_WhenGetElevatorByIdCalled_ThenCorrectElevatorReturned)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(3);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    manager.addElevator(
        std::make_unique<TestElevator>(1));

    manager.addElevator(
        std::make_unique<TestElevator>(2));

    ASSERT_NE(
        manager.getElevatorById(2),
        nullptr);

    EXPECT_EQ(
        manager.getElevatorById(2)->getId(),
        2);
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenObstructDoorCalled_ThenReturnsFalse)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_FALSE(
        manager.obstructDoor(0));
}

TEST_F(
    ElevatorManagerTest,
    GivenOneElevator_WhenClearObstructionCalled_ThenReturnsFalse)
{
    EXPECT_CALL(
        scheduler,
        registerElevator(_))
        .Times(1);

    manager.addElevator(
        std::make_unique<TestElevator>(0));

    EXPECT_FALSE(
        manager.clearObstruction(0));
}
