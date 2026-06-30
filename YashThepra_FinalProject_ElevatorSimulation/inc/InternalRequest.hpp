#pragma once

#include "AbstractRequest.hpp"

class InternalRequest : public AbstractRequest
{
public:
    InternalRequest(const int requestId, const int destinationFloor, const int elevatorId);

    bool isExpired() const override;
};
