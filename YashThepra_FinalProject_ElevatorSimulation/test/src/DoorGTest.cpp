#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "Door.hpp"

class DoorTest : public ::testing::Test
{
protected:
    Door* door;
    void SetUp() override
    {
        door = new Door(std::chrono::milliseconds(20));
    }
    void TearDown() override
    {
        delete door;
    }
};

TEST_F(DoorTest,
       GivenNewDoor_WhenConstructed_ThenInitialStateIsClosed)
{
    EXPECT_EQ(door->getState(), DoorState::Closed);
}

TEST_F(DoorTest,
       GivenNewDoor_WhenConstructed_ThenDoorIsNotObstructed)
{
    EXPECT_FALSE(door->isObstructed());
}

TEST_F(DoorTest,
       GivenClosedDoor_WhenOpenCalled_ThenDoorStateBecomesOpen)
{
    door->open();

    EXPECT_EQ(door->getState(), DoorState::Open);
}

TEST_F(DoorTest,
       GivenOpenDoor_WhenOpenCalledAgain_ThenDoorStateRemainsOpen)
{
    door->open();
    door->open();

    EXPECT_EQ(door->getState(), DoorState::Open);
}

TEST_F(DoorTest,
       GivenOpenDoor_WhenCloseCalled_ThenDoorStateBecomesClosed)
{
    door->open();

    door->close();

    EXPECT_EQ(door->getState(), DoorState::Closed);
}

TEST_F(DoorTest,
       GivenClosedDoor_WhenCloseCalled_ThenDoorStateRemainsClosed)
{
    door->close();

    EXPECT_EQ(door->getState(), DoorState::Closed);
}

TEST_F(DoorTest,
       GivenDoor_WhenObstructionEnabled_ThenDoorReportsObstructed)
{
    door->setObstructed(true);

    EXPECT_TRUE(door->isObstructed());
}

TEST_F(DoorTest,
       GivenObstructedDoor_WhenCloseCalled_ThenDoorStateBecomesBlocked)
{
    door->open();

    door->setObstructed(true);

    door->close();

    EXPECT_EQ(door->getState(), DoorState::Blocked);
}

TEST_F(DoorTest,
       GivenBlockedDoor_WhenObstructionRemovedAndCloseCalled_ThenDoorStateBecomesClosed)
{
    door->open();

    door->setObstructed(true);

    door->close();

    ASSERT_EQ(door->getState(), DoorState::Blocked);

    door->setObstructed(false);

    door->close();

    EXPECT_EQ(door->getState(), DoorState::Closed);
}

TEST_F(DoorTest,
       GivenOpenDoor_WhenOpenDurationExpires_ThenDoorAutomaticallyCloses)
{
    door->open();

    ASSERT_EQ(door->getState(), DoorState::Open);

    std::this_thread::sleep_for(std::chrono::milliseconds(350));

    EXPECT_EQ(door->getState(), DoorState::Closed);
}
