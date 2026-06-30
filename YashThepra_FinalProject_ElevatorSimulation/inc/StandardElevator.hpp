#pragma once

#include "Constant.hpp"
#include "Elevator.hpp"

#include <chrono>

class StandardElevator : public Elevator
{
public:
    using Duration = std::chrono::steady_clock::duration;

    StandardElevator(const int      elevatorId,
                     const int      minimumFloor,
                     const int      maximumFloor,
                     const Duration floorTravelTime = Constant::floorTravelTime);

protected:
    int  moveToFloor(const int targetFloor) override;

    void emergencyDescend()                 override;

    void serveRequest()                     override;

private:
    Duration floorTravelTime;
};
