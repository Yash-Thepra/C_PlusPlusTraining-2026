#include "LOOKStrategy.hpp"
#include "Elevator.hpp"

#include <limits>
#include <stdexcept>

int LOOKStrategy::computeCost(const Elevator& elevator,
                              const int       targetFloor,
                              Direction       requestDir) const
{
    const int  current   = elevator.getCurrentFloor();
    const auto direction = elevator.getDirection();
    const int  distance  = std::abs(current - targetFloor);

    const bool aheadOnPath = (direction == Direction::Up   && targetFloor >= current) ||
                            (direction == Direction::Down && targetFloor <= current);

    if (direction == Direction::None || elevator.getState() == ElevatorState::Idle)
    {
        return distance;
    }

    const auto requestQueueFront = elevator.getRequestQueueFront();
    if (!requestQueueFront.has_value())
    {
        return aheadOnPath ? distance : (distance * 2);
    }

    const int       floorInQueue     = requestQueueFront->first;
    const Direction directionInQueue = requestQueueFront->second;

    int cost = 0;

    if (direction == Direction::Up && requestDir == Direction::Up &&
        directionInQueue == Direction::Up && aheadOnPath)
    {
        cost = distance - 4;
    }
    else if (direction == Direction::Up && requestDir == Direction::Up &&
             directionInQueue == Direction::Up && !aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 2;
    }
    else if (direction == Direction::Up && requestDir == Direction::Up &&
             directionInQueue == Direction::Down)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    else if (direction == Direction::Up && requestDir == Direction::Down &&
             directionInQueue == Direction::Down && aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) - 2;
    }
    else if (direction == Direction::Up && requestDir == Direction::Down &&
             directionInQueue == Direction::Down && !aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    else if (direction == Direction::Up && requestDir == Direction::Down &&
             directionInQueue == Direction::Up)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    else if (direction == Direction::Down && requestDir == Direction::Down &&
             directionInQueue == Direction::Down && aheadOnPath)
    {
        cost = distance - 4;
    }
    else if (direction == Direction::Down && requestDir == Direction::Down &&
             directionInQueue == Direction::Down && !aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 2;
    }
    else if (direction == Direction::Down && requestDir == Direction::Down &&
             directionInQueue == Direction::Up)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    else if (direction == Direction::Down && requestDir == Direction::Up &&
             directionInQueue == Direction::Up && aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) - 2;
    }
    else if (direction == Direction::Down && requestDir == Direction::Up &&
             directionInQueue == Direction::Up && !aheadOnPath)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    else if (direction == Direction::Down && requestDir == Direction::Up &&
             directionInQueue == Direction::Down)
    {
        cost = std::abs(current - floorInQueue) + std::abs(floorInQueue - targetFloor) + 4;
    }
    return cost;
}

int LOOKStrategy::selectElevator(const IRequest&               request,
                                 const std::vector<Elevator*>& elevators,
                                 const DispatchContext&        /*context*/) const
{
    if (elevators.empty())
    {
        throw std::runtime_error{"LOOKStrategy: no elevators registered"};
    }
    int bestId{elevators.front()->getId()};
    int bestCost{std::numeric_limits<int>::max()};
    for (const auto* elevator : elevators)
    {
        if (elevator == nullptr) continue;
        {

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
