#include "AbstractRequest.hpp"

AbstractRequest::AbstractRequest(const RequestConfiguration& configuration)
    : floor{configuration.floor}
    , direction{configuration.direction}
    , type{configuration.type}
    , priority{configuration.priority}
    , Id{configuration.id}
    , timestamp{std::chrono::steady_clock::now()}
{
}

Direction AbstractRequest::getDirection() const
{
    return direction;
}

int AbstractRequest::getFloor() const
{
    return floor;
}

int AbstractRequest::getPriority() const
{
    return priority;
}

int AbstractRequest::getId() const
{
    return Id;
}

RequestType AbstractRequest::getType() const
{
    return type;
}
