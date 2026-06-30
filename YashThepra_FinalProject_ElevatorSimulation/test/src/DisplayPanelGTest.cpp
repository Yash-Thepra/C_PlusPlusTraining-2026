#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "DisplayPanel.hpp"

class DisplayPanelTest : public ::testing::Test
{
protected:
    std::ostringstream outputStream;
    DisplayPanel* displayPanel;

    void SetUp() override
    {
        displayPanel = new DisplayPanel(2, outputStream);
    }

    void TearDown() override
    {
        delete displayPanel;
    }
};

TEST_F(
    DisplayPanelTest,
    GivenNewDisplayPanel_WhenRenderIsCalled_ThenGroundFloorIsDisplayed)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("G"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenNewDisplayPanel_WhenRenderIsCalled_ThenElevatorZeroIsDisplayed)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("Elevator 0"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenNewDisplayPanel_WhenRenderIsCalled_ThenElevatorOneIsDisplayed)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("Elevator 1"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenNewDisplayPanel_WhenRenderIsCalled_ThenIdleStateIsDisplayed)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("IDLE"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenMovingUpState_WhenRenderIsCalled_ThenMovingUpStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingUp);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("MOVING UP"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenMovingDownState_WhenRenderIsCalled_ThenMovingDownStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingDown);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("MOVING DOWN"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDoorOpenState_WhenRenderIsCalled_ThenDoorOpenStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::DoorOpen);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("DOOR OPEN"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDoorClosedState_WhenRenderIsCalled_ThenDoorClosedStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::DoorClosed);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("DOOR CLOSED"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenMaintenanceState_WhenRenderIsCalled_ThenMaintenanceStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::Maintenance);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("MAINTENANCE"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenOutOfServiceState_WhenRenderIsCalled_ThenOutOfServiceStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::OutOfService);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("OUT OF SERVICE"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenEmergencyStopState_WhenRenderIsCalled_ThenEmergencyStopStateIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::EmergencyStop);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("EMERGENCY STOP"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenFloorArrival_WhenRenderIsCalled_ThenArrivalEventIsDisplayed)
{
    displayPanel->onFloorArrival(0, 3);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("arrived"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenRequestServiced_WhenRenderIsCalled_ThenServiceEventIsDisplayed)
{
    displayPanel->onRequestServiced(0, 3);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("serviced"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenIdleElevator_WhenStateChangesToMovingUp_ThenUpDirectionIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingUp);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("▲"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenIdleElevator_WhenStateChangesToMovingDown_ThenDownDirectionIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingDown);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("▼"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenMovingElevator_WhenStateChangesToIdle_ThenIdleDirectionIsDisplayed)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingUp);
    displayPanel->onStateChanged(0, ElevatorState::Idle);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("IDLE"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenMultipleElevators_WhenDifferentStatesAreAssigned_ThenAllStatesAreRendered)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingUp);
    displayPanel->onStateChanged(1, ElevatorState::DoorOpen);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("MOVING UP"), std::string::npos);
    EXPECT_NE(outputStream.str().find("DOOR OPEN"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenSingleEventIsAdded_ThenEventAppearsInRenderOutput)
{
    displayPanel->pushEvent("Test Event");

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("Test Event"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenMaximumLogSizeIsExceeded_ThenOldestEventIsDiscarded)
{
    for (int i = 0; i < 10; ++i)
    {
        displayPanel->pushEvent("Event " + std::to_string(i));
    }

    displayPanel->render();

    EXPECT_EQ(outputStream.str().find("Event 0"), std::string::npos);
    EXPECT_EQ(outputStream.str().find("Event 1"), std::string::npos);

    EXPECT_NE(outputStream.str().find("Event 2"), std::string::npos);
    EXPECT_NE(outputStream.str().find("Event 9"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenNoEventsExist_ThenWaitingMessageIsRendered)
{
    displayPanel->render();

    EXPECT_NE(
        outputStream.str().find("(waiting for requests...)"),
        std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenStateChangesRepeatedly_ThenLatestStateIsRendered)
{
    displayPanel->onStateChanged(0, ElevatorState::MovingUp);
    displayPanel->onStateChanged(0, ElevatorState::DoorOpen);
    displayPanel->onStateChanged(0, ElevatorState::Idle);

    displayPanel->render();

    EXPECT_NE(outputStream.str().find("IDLE"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenRenderIsCalled_ThenStatusSectionIsPresent)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("STATUS:"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenRenderIsCalled_ThenEventsSectionIsPresent)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("EVENTS:"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenRenderIsCalled_ThenFloorHeaderIsPresent)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("Floor"), std::string::npos);
}

TEST_F(
    DisplayPanelTest,
    GivenDisplayPanel_WhenRenderIsCalled_ThenElevatorHeadersArePresent)
{
    displayPanel->render();

    EXPECT_NE(outputStream.str().find("Elevator 0"), std::string::npos);
    EXPECT_NE(outputStream.str().find("Elevator 1"), std::string::npos);
}
