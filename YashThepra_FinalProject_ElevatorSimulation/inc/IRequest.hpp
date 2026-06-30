#pragma once

#include <chrono>

enum class Direction
{
    Up,
    Down,
    None
};

enum class RequestType
{
    ExternalUp,
    ExternalDown,
    Internal,
    Emergency
};

class IRequest
{
public:
    using TimePoint = std::chrono::steady_clock::time_point;
    
    virtual ~IRequest() = default;

    virtual Direction                             getDirection() const = 0;

    virtual int                                   getFloor()     const = 0;
    
    virtual int                                   getPriority()  const = 0;

    virtual int                                   getId()        const = 0;

    virtual RequestType                           getType()      const = 0;

    virtual bool                                  isExpired()    const = 0;
};
