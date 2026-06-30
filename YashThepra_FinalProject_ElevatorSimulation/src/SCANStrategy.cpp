#include "SCANStrategy.hpp"
#include "Elevator.hpp"

#include <limits>
#include <stdexcept>

SCANStrategy::SCANStrategy(const int minimumFloor, const int maximumFloor)
    : minimumFloor{minimumFloor}
    , maximumFloor{maximumFloor}
{
}

int SCANStrategy::computeCost(const Elevator& elevator, 
                              const int       targetFloor, 
                              Direction       requestDir) const
{
    const int  current           = elevator.getCurrentFloor();
    const auto direction         = elevator.getDirection();
    const int  distance          = std::abs(current - targetFloor);
    const auto requestQueueFront = elevator.getRequestQueueFront();
    const bool directionMatches  = (direction == requestDir);
    const bool aheadOnPath       = (direction == Direction::Up   && targetFloor >= current) ||
                                  (direction == Direction::Down && targetFloor <= current);

    int        cost              = 0;
    if (direction == Direction::None || elevator.getState() == ElevatorState::Idle)
    {
        cost =  distance;
    }
    else if (directionMatches && aheadOnPath)
    {
        cost =  distance;
    }
    else
    {
        const int boundary = (direction == Direction::Up) ? maximumFloor : minimumFloor;
        cost =  std::abs(current - boundary) + std::abs(boundary - targetFloor);
    }
    return cost;
}

int SCANStrategy::selectElevator(const IRequest&                request,
                                 const std::vector<Elevator*>&  elevators,
                                 const DispatchContext&         context) const
{
    if (elevators.empty())
    {
        throw std::runtime_error{"SCANStrategy: no elevators registered"};
    }
    int bestId = elevators.front()->getId();
    int bestCost = std::numeric_limits<int>::max();
    for (const auto* elevator : elevators)
    {
        if (elevator == nullptr)
        {
            continue;
        }
        if (elevator->getState() == ElevatorState::OutOfService  ||
            elevator->getState() == ElevatorState::Maintenance   ||
            elevator->getState() == ElevatorState::EmergencyStop)
        {
            continue;
        }
        const int cost = computeCost(*elevator, request.getFloor(), request.getDirection());
        if (cost < bestCost)
        {
            bestCost = cost;
            bestId   = elevator->getId();
        }
    }
    return bestId;
}
