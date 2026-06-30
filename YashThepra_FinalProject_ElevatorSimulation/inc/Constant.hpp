#pragma once

#include <chrono>
#include <string_view>

namespace Constant
{
    inline constexpr int defaultFloorInEmergency       = 0;
    inline constexpr int emergencyRequestPriority      = 100;
    inline constexpr int fcfsQueueThreshold            = 1;
    inline constexpr int groundFloor                   = 0;
    inline constexpr int maximumFloor                  = 7;
    inline constexpr int minimumBasementFloor          = -2;
    inline constexpr int normalRequestPriority         = 10;
    inline constexpr int scanQueueThreshold            = 7;
    inline constexpr int totalElevators                = 2;
    inline constexpr float maximumWeightInKg           = 680.0F;
    inline constexpr float overloadThresholdInKg       = 650.0F;
    inline constexpr auto doorCloseRetryDelay          = std::chrono::milliseconds{500};
    inline constexpr auto doorOpenDuration             = std::chrono::milliseconds{2000};
    inline constexpr auto floorTravelTime              = std::chrono::milliseconds{1600};
    inline constexpr auto requestTimeToLive            = std::chrono::seconds{120};
    inline constexpr auto schedulerTickInterval        = std::chrono::milliseconds{200};
    inline constexpr auto userInterfaceRefreshInterval = std::chrono::milliseconds{150};
    inline constexpr std::string_view basementLabel    = "B";
    inline constexpr std::string_view groundLabel      = "G";
}
