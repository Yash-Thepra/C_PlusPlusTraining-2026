#pragma once

#include "IRequest.hpp"

#include <string_view>
#include <vector>

class Elevator;

struct DispatchContext
{
    int pendingQueueSize = 0;   
    int busyElevators    = 0;       
    int totalElevators   = 0;
};

class IDispatchStrategy
{
public:
    virtual ~IDispatchStrategy() {};

    virtual int selectElevator(const IRequest&               request,
                               const std::vector<Elevator*>& elevators,
                               const DispatchContext&        context) const = 0;
};
