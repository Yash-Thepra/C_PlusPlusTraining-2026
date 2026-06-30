#include "AdaptiveStrategy.hpp"
#include "Constant.hpp"
#include "Elevator.hpp"
#include "FCFSStrategy.hpp"
#include "LOOKStrategy.hpp"
#include "SCANStrategy.hpp"

AdaptiveStrategy::AdaptiveStrategy(const int minimumFloor, const int maximumFloor)
    : fcfs{std::make_unique<FCFSStrategy>()}
    , look{std::make_unique<LOOKStrategy>()}
    , scan{std::make_unique<SCANStrategy>(minimumFloor, maximumFloor)}
    , active{fcfs.get()}
{
}

IDispatchStrategy& AdaptiveStrategy::pick(const DispatchContext& context) const
{
    const bool allElevatorIdle = (context.busyElevators == 0);
    if (allElevatorIdle && context.pendingQueueSize <= Constant::fcfsQueueThreshold)
    {
        active = fcfs.get();
    }
    else if (context.pendingQueueSize >= Constant::scanQueueThreshold)
    {
        active = scan.get();
    }
    else
    {
        active = look.get();
    }
    return *active;
}

int AdaptiveStrategy::selectElevator(const IRequest&               request,
                                     const std::vector<Elevator*>& elevators,
                                     const DispatchContext&        context) const
{
    return pick(context).selectElevator(request, elevators, context);
}
