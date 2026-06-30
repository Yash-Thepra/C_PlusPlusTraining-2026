#include <gtest/gtest.h>

#include "FloorPanel.hpp"

class FloorPanelTest : public ::testing::Test
{
protected:
    FloorPanel* panel;
    void SetUp() override
    {
        panel = new FloorPanel(5);
    }

    void TearDown() override
    {
        delete panel;
    }
};

TEST_F(FloorPanelTest,
       GivenNewFloorPanel_WhenConstructed_ThenFloorNumberIsInitialized)
{
    EXPECT_EQ(panel->getFloorNumber(), 5);
}

TEST_F(FloorPanelTest,
       GivenNewFloorPanel_WhenConstructed_ThenUpButtonIsNotIlluminated)
{
    EXPECT_FALSE(panel->isUpLit());
}

TEST_F(FloorPanelTest,
       GivenNewFloorPanel_WhenConstructed_ThenDownButtonIsNotIlluminated)
{
    EXPECT_FALSE(panel->isDownLit());
}

TEST_F(FloorPanelTest,
       GivenPanel_WhenIlluminateUpCalled_ThenUpButtonBecomesIlluminated)
{
    panel->illuminate(Direction::Up);

    EXPECT_TRUE(panel->isUpLit());
}

TEST_F(FloorPanelTest,
       GivenPanel_WhenIlluminateDownCalled_ThenDownButtonBecomesIlluminated)
{
    panel->illuminate(Direction::Down);

    EXPECT_TRUE(panel->isDownLit());
}

TEST_F(FloorPanelTest,
       GivenIlluminatedUpButton_WhenExtinguishCalled_ThenUpButtonTurnsOff)
{
    panel->illuminate(Direction::Up);

    panel->extinguish(Direction::Up);

    EXPECT_FALSE(panel->isUpLit());
}

TEST_F(FloorPanelTest,
       GivenIlluminatedDownButton_WhenExtinguishCalled_ThenDownButtonTurnsOff)
{
    panel->illuminate(Direction::Down);

    panel->extinguish(Direction::Down);

    EXPECT_FALSE(panel->isDownLit());
}

TEST_F(FloorPanelTest,
       GivenPanel_WhenUpButtonPressed_ThenUpButtonIsIlluminated)
{
    panel->pressUp();

    EXPECT_TRUE(panel->isUpLit());
}

TEST_F(FloorPanelTest,
       GivenPanel_WhenDownButtonPressed_ThenDownButtonIsIlluminated)
{
    panel->pressDown();

    EXPECT_TRUE(panel->isDownLit());
}

TEST_F(FloorPanelTest,
       GivenRegisteredCallback_WhenUpButtonPressed_ThenCallbackReceivesCorrectArguments)
{
    bool callbackInvoked = false;
    int floor = -1;
    Direction direction = Direction::None;

    panel->setButtonCallback(
        [&](int receivedFloor, Direction receivedDirection)
        {
            callbackInvoked = true;
            floor = receivedFloor;
            direction = receivedDirection;
        });

    panel->pressUp();

    EXPECT_TRUE(callbackInvoked);
    EXPECT_EQ(floor, 5);
    EXPECT_EQ(direction, Direction::Up);
}

TEST_F(FloorPanelTest,
       GivenRegisteredCallback_WhenDownButtonPressed_ThenCallbackReceivesCorrectArguments)
{
    bool callbackInvoked = false;
    int floor = -1;
    Direction direction = Direction::None;

    panel->setButtonCallback(
        [&](int receivedFloor, Direction receivedDirection)
        {
            callbackInvoked = true;
            floor = receivedFloor;
            direction = receivedDirection;
        });

    panel->pressDown();

    EXPECT_TRUE(callbackInvoked);
    EXPECT_EQ(floor, 5);
    EXPECT_EQ(direction, Direction::Down);
}
