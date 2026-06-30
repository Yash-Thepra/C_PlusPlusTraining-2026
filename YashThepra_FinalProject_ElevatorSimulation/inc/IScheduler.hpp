#pragma once

#include "IDispatchStrategy.hpp"
#include "IRequest.hpp"

#include <memory>

class Elevator;

class IScheduler
{
public:
    virtual ~IScheduler() {};

    virtual IDispatchStrategy* getStrategy()                                     const = 0;

    virtual void               processNext()                                           = 0;

    virtual void               registerElevator(Elevator* elevator)                    = 0;

    virtual void               schedule(const IRequest& request)                       = 0;
    
    virtual void               setStrategy(std::unique_ptr<IDispatchStrategy> strategy) = 0;
};
