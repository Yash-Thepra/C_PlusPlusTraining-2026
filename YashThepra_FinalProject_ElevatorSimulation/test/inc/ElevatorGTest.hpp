#pragma once

#include "StandardElevator.hpp"

class TestElevator : public StandardElevator
{
public:
    TestElevator(
        int id,
        int minimumFloor = Constant::minimumBasementFloor,
        int maximumFloor = Constant::maximumFloor)
        : StandardElevator(
              id,
              minimumFloor,
              maximumFloor,
              std::chrono::milliseconds{0})
    {
    }

    using Elevator::setCurrentFloor;
    using Elevator::setDirection;
    using Elevator::setState;
    using Elevator::estimateArrival;
    using Elevator::getCurrentFloor;
    using Elevator::getDirection;
    using Elevator::getId;
    using Elevator::getRequestQueueFront;
    using Elevator::getState;

    using Elevator::notifyFloorArrival;
    using Elevator::notifyRequestServiced;
    using Elevator::notifyStateChanged;

    using Elevator::sortQueue;

    using StandardElevator::emergencyDescend;
    using StandardElevator::moveToFloor;
    using StandardElevator::serveRequest;
};
