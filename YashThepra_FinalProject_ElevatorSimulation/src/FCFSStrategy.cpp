#include "FCFSStrategy.hpp"
#include "Elevator.hpp"

#include <limits>
#include <stdexcept>

int FCFSStrategy::selectElevator(const IRequest&               request,
                                 const std::vector<Elevator*>& elevators,
                                 const DispatchContext&        context) const
{
    if (elevators.empty())
    {
        throw std::runtime_error{"FCFSStrategy: no elevators registered"};
    }
    int  bestId     = elevators.front()->getId();
    int  bestEta    = std::numeric_limits<int>::max();
    bool bestIsIdle = false;
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
        const bool isIdle                 = (elevator->getState() == ElevatorState::Idle);
        const int  estimatedTimeOfArrival = elevator->estimateArrival(request.getFloor());
        const bool better = bestIsIdle ? (isIdle && estimatedTimeOfArrival < bestEta)     
                                       : (isIdle || estimatedTimeOfArrival < bestEta);       
        if (better)
        {
            bestEta    = estimatedTimeOfArrival;
            bestId     = elevator->getId();
            bestIsIdle = isIdle;
        }
    }
    return bestId;
}
