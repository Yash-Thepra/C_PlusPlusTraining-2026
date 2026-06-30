#include <gtest/gtest.h>

#include "Building.hpp"
#include "SchedulerGMock.hpp"

class BuildingTest : public ::testing::Test
{
protected:
    SchedulerGMock scheduler;

    Building building{
        "Test Building",
        Constant::minimumBasementFloor,
        Constant::maximumFloor,
        &scheduler};
};

TEST_F(
    BuildingTest,
    GivenValidArguments_WhenConstructed_ThenBuildingNameIsInitialized)
{
    EXPECT_EQ(
        building.getName(),
        "Test Building");
}

TEST_F(
    BuildingTest,
    GivenNullScheduler_WhenConstructed_ThenElevatorManagerExists)
{
    EXPECT_NE(
        building.getElevatorManager(),
        nullptr);
}

TEST(
    BuildingConstructorTest,
    GivenEmptyName_WhenConstructed_ThenThrowsInvalidArgument)
{
    SchedulerGMock scheduler;

    EXPECT_THROW(
        Building(
            "",
            Constant::minimumBasementFloor,
            Constant::maximumFloor,
            &scheduler),
        std::invalid_argument);
}

TEST(
    BuildingConstructorTest,
    GivenInvalidFloorRange_WhenConstructed_ThenThrowsInvalidArgument)
{
    SchedulerGMock scheduler;

    EXPECT_THROW(
        Building(
            "Test",
            5,
            5,
            &scheduler),
        std::invalid_argument);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenInitialized_ThenGroundFloorExists)
{
    building.initialize();

    EXPECT_NE(
        building.getFloor(Constant::groundFloor),
        nullptr);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenInitialized_ThenMinimumFloorExists)
{
    building.initialize();

    EXPECT_NE(
        building.getFloor(Constant::minimumBasementFloor),
        nullptr);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenInitialized_ThenMaximumFloorExists)
{
    building.initialize();

    EXPECT_NE(
        building.getFloor(Constant::maximumFloor),
        nullptr);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenRequestingFloorBelowMinimum_ThenThrowsOutOfRange)
{
    building.initialize();

    EXPECT_THROW(
        building.getFloor(
            Constant::minimumBasementFloor - 1),
        std::out_of_range);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenRequestingFloorAboveMaximum_ThenThrowsOutOfRange)
{
    building.initialize();

    EXPECT_THROW(
        building.getFloor(
            Constant::maximumFloor + 1),
        std::out_of_range);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenGetElevatorManagerCalledMultipleTimes_ThenSamePointerReturned)
{
    EXPECT_EQ(
        building.getElevatorManager(),
        building.getElevatorManager());
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenInitializedTwice_ThenNoExceptionThrown)
{
    building.initialize();

    EXPECT_NO_THROW(
        building.initialize());
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenGettingGroundFloorMultipleTimes_ThenSamePointerReturned)
{
    building.initialize();

    Floor* first =
        building.getFloor(Constant::groundFloor);

    Floor* second =
        building.getFloor(Constant::groundFloor);

    EXPECT_EQ(
        first,
        second);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenGettingMinimumFloor_ThenCorrectFloorReturned)
{
    building.initialize();

    EXPECT_EQ(
        building.getFloor(Constant::minimumBasementFloor)->getFloorNumber(),
        Constant::minimumBasementFloor);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenGettingMaximumFloor_ThenCorrectFloorReturned)
{
    building.initialize();

    EXPECT_EQ(
        building.getFloor(Constant::maximumFloor)->getFloorNumber(),
        Constant::maximumFloor);
}

TEST_F(
    BuildingTest,
    GivenInitializedBuilding_WhenGettingEveryFloor_ThenAllFloorsExist)
{
    building.initialize();

    for (int floor = Constant::minimumBasementFloor;
         floor <= Constant::maximumFloor;
         ++floor)
    {
        EXPECT_NE(
            building.getFloor(floor),
            nullptr);
    }
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenGetNameCalledMultipleTimes_ThenSameNameReturned)
{
    EXPECT_EQ(
        building.getName(),
        building.getName());
}

TEST_F(
    BuildingTest,
    GivenInitializedBuilding_WhenElevatorManagerRequested_ThenPointerRemainsValid)
{
    building.initialize();

    EXPECT_NE(
        building.getElevatorManager(),
        nullptr);
}

TEST_F(
    BuildingTest,
    GivenInitializedBuilding_WhenGroundFloorRequested_ThenGroundFloorNumberMatches)
{
    building.initialize();

    EXPECT_EQ(
        building.getFloor(Constant::groundFloor)->getFloorNumber(),
        Constant::groundFloor);
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenInitializeCalled_ThenNoExceptionThrown)
{
    EXPECT_NO_THROW(
        building.initialize());
}

TEST_F(
    BuildingTest,
    GivenBuilding_WhenFloorRetrievedRepeatedly_ThenObjectRemainsValid)
{
    building.initialize();

    for (int index = 0; index < 5; ++index)
    {
        EXPECT_NE(
            building.getFloor(Constant::groundFloor),
            nullptr);
    }
}
