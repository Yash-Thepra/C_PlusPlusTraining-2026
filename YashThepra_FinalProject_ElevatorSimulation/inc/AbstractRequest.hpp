#pragma once

#include "IRequest.hpp"

#include <chrono>

struct RequestConfiguration
{
    int floor;
    Direction direction;
    RequestType type;
    int priority;
    int id;
};

class AbstractRequest : public IRequest
{
public:
    AbstractRequest(const RequestConfiguration& configuration);

    ~AbstractRequest() override {};

    Direction                             getDirection() const override;

    int                                   getFloor()     const override;

    int                                   getPriority()  const override;

    int                                   getId()        const override;

    RequestType                           getType()      const override;

    bool                                  isExpired()    const override = 0;

protected:
    Direction                             direction;
    int                                   floor;
    int                                   priority;
    int                                   Id;
    TimePoint                             timestamp;
    RequestType                           type;
};
