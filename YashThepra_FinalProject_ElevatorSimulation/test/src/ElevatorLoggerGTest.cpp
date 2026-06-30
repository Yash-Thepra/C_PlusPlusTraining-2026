#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "ElevatorLogger.hpp"

class ElevatorLoggerTest : public ::testing::Test
{
protected:
    std::ostringstream outputStream;
    ElevatorLogger logger{outputStream};
};

TEST_F(
    ElevatorLoggerTest,
    GivenFloorArrival_WhenLogged_ThenArrivalMessageIsWritten)
{
    logger.onFloorArrival(0, 5);

    const std::string output = outputStream.str();

    EXPECT_NE(output.find("ELEV-0"), std::string::npos);
    EXPECT_NE(output.find("arrived at floor 5"), std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenRequestServiced_WhenLogged_ThenServiceMessageIsWritten)
{
    logger.onRequestServiced(1, 7);

    const std::string output = outputStream.str();

    EXPECT_NE(output.find("ELEV-1"), std::string::npos);
    EXPECT_NE(output.find("serviced floor 7"), std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenIdleState_WhenLogged_ThenIdleStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::Idle);

    EXPECT_NE(
        outputStream.str().find("IDLE"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenMovingUpState_WhenLogged_ThenMovingUpStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::MovingUp);

    EXPECT_NE(
        outputStream.str().find("MOVING_UP"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenMovingDownState_WhenLogged_ThenMovingDownStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::MovingDown);

    EXPECT_NE(
        outputStream.str().find("MOVING_DOWN"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenDoorOpenState_WhenLogged_ThenDoorOpenStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::DoorOpen);

    EXPECT_NE(
        outputStream.str().find("DOOR_OPEN"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenDoorClosedState_WhenLogged_ThenDoorClosedStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::DoorClosed);

    EXPECT_NE(
        outputStream.str().find("DOOR_CLOSED"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenMaintenanceState_WhenLogged_ThenMaintenanceStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::Maintenance);

    EXPECT_NE(
        outputStream.str().find("MAINTENANCE"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenOutOfServiceState_WhenLogged_ThenOutOfServiceStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::OutOfService);

    EXPECT_NE(
        outputStream.str().find("OUT_OF_SERVICE"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenEmergencyStopState_WhenLogged_ThenEmergencyStopStateIsWritten)
{
    logger.onStateChanged(0, ElevatorState::EmergencyStop);

    EXPECT_NE(
        outputStream.str().find("EMERGENCY_STOP"),
        std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenMultipleEvents_WhenLogged_ThenAllEventsAppearInOutput)
{
    logger.onFloorArrival(0, 2);
    logger.onRequestServiced(0, 2);
    logger.onStateChanged(0, ElevatorState::Idle);

    const std::string output = outputStream.str();

    EXPECT_NE(output.find("arrived at floor 2"), std::string::npos);
    EXPECT_NE(output.find("serviced floor 2"), std::string::npos);
    EXPECT_NE(output.find("IDLE"), std::string::npos);
}

TEST_F(
    ElevatorLoggerTest,
    GivenLogEntry_WhenWritten_ThenTimestampIsPresent)
{
    logger.onFloorArrival(1, 3);

    const std::string output = outputStream.str();

    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}
