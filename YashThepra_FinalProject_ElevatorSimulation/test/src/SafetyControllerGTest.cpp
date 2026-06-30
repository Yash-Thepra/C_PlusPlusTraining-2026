#include <gtest/gtest.h>

#include "SafetyController.hpp"

class SafetyControllerTest : public ::testing::Test
{
};

TEST_F(
    SafetyControllerTest,
    GivenValidMaximumWeight_WhenConstructed_ThenControllerIsOperational)
{
    SafetyController controller;

    EXPECT_TRUE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenPositiveMaximumWeight_WhenConstructed_ThenControllerIsOperational)
{
    SafetyController controller(500.0F);

    EXPECT_TRUE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenZeroMaximumWeight_WhenConstructed_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        SafetyController controller(0.0F),
        std::invalid_argument);
}

TEST_F(
    SafetyControllerTest,
    GivenNegativeMaximumWeight_WhenConstructed_ThenInvalidArgumentExceptionIsThrown)
{
    EXPECT_THROW(
        SafetyController controller(-10.0F),
        std::invalid_argument);
}

TEST_F(
    SafetyControllerTest,
    GivenOperationalController_WhenPowerFailureOccurs_ThenControllerBecomesNonOperational)
{
    SafetyController controller;

    controller.onPowerFailure();

    EXPECT_FALSE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenOperationalController_WhenEmergencyIsTriggered_ThenControllerBecomesNonOperational)
{
    SafetyController controller;

    controller.triggerEmergency();

    EXPECT_FALSE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenPowerFailure_WhenResetSafetyIsCalled_ThenControllerBecomesOperational)
{
    SafetyController controller;

    controller.onPowerFailure();

    controller.resetSafety();

    EXPECT_TRUE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenEmergencyTriggered_WhenResetSafetyIsCalled_ThenControllerBecomesOperational)
{
    SafetyController controller;

    controller.triggerEmergency();

    controller.resetSafety();

    EXPECT_TRUE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenMultiplePowerFailures_WhenControllerIsChecked_ThenControllerRemainsNonOperational)
{
    SafetyController controller;

    controller.onPowerFailure();
    controller.onPowerFailure();

    EXPECT_FALSE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenMultipleEmergencyTriggers_WhenControllerIsChecked_ThenControllerRemainsNonOperational)
{
    SafetyController controller;

    controller.triggerEmergency();
    controller.triggerEmergency();

    EXPECT_FALSE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenMultipleResetOperations_WhenControllerIsChecked_ThenControllerRemainsOperational)
{
    SafetyController controller;

    controller.resetSafety();
    controller.resetSafety();

    EXPECT_TRUE(controller.isOperational());
}

TEST_F(
    SafetyControllerTest,
    GivenPowerFailureAndEmergency_WhenResetSafetyIsCalled_ThenControllerBecomesOperational)
{
    SafetyController controller;

    controller.onPowerFailure();
    controller.triggerEmergency();

    controller.resetSafety();

    EXPECT_TRUE(controller.isOperational());
}
