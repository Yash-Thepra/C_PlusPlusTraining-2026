#include "RequestFactory.hpp"
#include "Constant.hpp"
#include "ExternalRequest.hpp"
#include "InternalRequest.hpp"

#include <atomic>
#include <stdexcept>

namespace
{
    std::atomic<int> g_nextId = 1;
} 

std::unique_ptr<IRequest> RequestFactory::createExternal(const int floor,
                                                        Direction  direction)
{
    if (floor < Constant::minimumBasementFloor || floor > Constant::maximumFloor)
    {
        throw std::out_of_range{"createExternal: floor out of range"};
    }
    if (direction == Direction::None)
    {
        throw std::invalid_argument{"createExternal: direction must be Up or Down"};
    }
    return std::make_unique<ExternalRequest>(floor, direction, nextId());
}

std::unique_ptr<IRequest> RequestFactory::createInternal(const int elevatorId,
                                                         const int destinationFloor)
{
    if (destinationFloor < Constant::minimumBasementFloor ||
        destinationFloor > Constant::maximumFloor)
    {
        throw std::out_of_range{"createInternal: floor out of range"};
    }
    if (elevatorId < 0 || elevatorId >= Constant::totalElevators)
    {
        throw std::invalid_argument{"createInternal: invalid elevatorId"};
    }
    return std::make_unique<InternalRequest>(elevatorId, destinationFloor, nextId());
}

int RequestFactory::nextId()
{
    return g_nextId.fetch_add(1, std::memory_order_relaxed);
}
