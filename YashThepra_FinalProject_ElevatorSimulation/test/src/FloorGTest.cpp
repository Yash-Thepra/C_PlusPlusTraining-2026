#include <gtest/gtest.h>

#include "Floor.hpp"

class FloorTest : public ::testing::Test
{
protected:
    Floor* groundFloor;
    Floor* basementFloor;
    Floor* regularFloor;

    void SetUp() override
    {
        groundFloor = new Floor(0, true, true);
        basementFloor = new Floor(-2, true, false);
        regularFloor = new Floor(5, false, true);
    }

    void TearDown() override
    {
        delete groundFloor;
        delete basementFloor;
        delete regularFloor;
    }
};

TEST_F(
    FloorTest,
    GivenGroundFloor_WhenConstructed_ThenFloorNumberIsInitialized)
{
    EXPECT_EQ(groundFloor->getFloorNumber(), 0);
}

TEST_F(
    FloorTest,
    GivenBasementFloor_WhenConstructed_ThenFloorNumberIsInitialized)
{
    EXPECT_EQ(basementFloor->getFloorNumber(), -2);
}

TEST_F(
    FloorTest,
    GivenRegularFloor_WhenConstructed_ThenFloorNumberIsInitialized)
{
    EXPECT_EQ(regularFloor->getFloorNumber(), 5);
}

TEST_F(
    FloorTest,
    GivenGroundFloor_WhenGetLabelIsCalled_ThenGroundLabelIsReturned)
{
    EXPECT_EQ(groundFloor->getLabel(), "G");
}

TEST_F(
    FloorTest,
    GivenBasementFloor_WhenGetLabelIsCalled_ThenBasementLabelIsReturned)
{
    EXPECT_EQ(basementFloor->getLabel(), "B2");
}

TEST_F(
    FloorTest,
    GivenRegularFloor_WhenGetLabelIsCalled_ThenFloorNumberStringIsReturned)
{
    EXPECT_EQ(regularFloor->getLabel(), "5");
}

TEST_F(
    FloorTest,
    GivenFloor_WhenGetPanelIsCalled_ThenValidPanelPointerIsReturned)
{
    EXPECT_NE(groundFloor->getPanel(), nullptr);
}

TEST_F(
    FloorTest,
    GivenFloorWithUpButton_WhenHasUpButtonIsCalled_ThenTrueIsReturned)
{
    EXPECT_TRUE(groundFloor->hasUpButton());
}

TEST_F(
    FloorTest,
    GivenFloorWithoutUpButton_WhenHasUpButtonIsCalled_ThenFalseIsReturned)
{
    EXPECT_FALSE(regularFloor->hasUpButton());
}

TEST_F(
    FloorTest,
    GivenFloorWithDownButton_WhenHasDownButtonIsCalled_ThenTrueIsReturned)
{
    EXPECT_TRUE(groundFloor->hasDownButton());
}

TEST_F(
    FloorTest,
    GivenFloorWithoutDownButton_WhenHasDownButtonIsCalled_ThenFalseIsReturned)
{
    EXPECT_FALSE(basementFloor->hasDownButton());
}

TEST_F(
    FloorTest,
    GivenFloorWithUpButton_WhenPressUpIsCalled_ThenUpButtonIsIlluminated)
{
    ASSERT_NE(groundFloor->getPanel(), nullptr);

    groundFloor->pressUp();

    EXPECT_TRUE(groundFloor->getPanel()->isUpLit());
}

TEST_F(
    FloorTest,
    GivenFloorWithoutUpButton_WhenPressUpIsCalled_ThenUpButtonRemainsOff)
{
    ASSERT_NE(regularFloor->getPanel(), nullptr);

    regularFloor->pressUp();

    EXPECT_FALSE(regularFloor->getPanel()->isUpLit());
}

TEST_F(
    FloorTest,
    GivenFloorWithDownButton_WhenPressDownIsCalled_ThenDownButtonIsIlluminated)
{
    ASSERT_NE(groundFloor->getPanel(), nullptr);

    groundFloor->pressDown();

    EXPECT_TRUE(groundFloor->getPanel()->isDownLit());
}

TEST_F(
    FloorTest,
    GivenFloorWithoutDownButton_WhenPressDownIsCalled_ThenDownButtonRemainsOff)
{
    ASSERT_NE(basementFloor->getPanel(), nullptr);

    basementFloor->pressDown();

    EXPECT_FALSE(basementFloor->getPanel()->isDownLit());
}

TEST_F(
    FloorTest,
    GivenFloor_WhenGetPanelIsCalledMultipleTimes_ThenSamePanelInstanceIsReturned)
{
    EXPECT_EQ(groundFloor->getPanel(), groundFloor->getPanel());
}
