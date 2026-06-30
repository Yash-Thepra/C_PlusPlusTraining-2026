#pragma once

#include "IDispatchStrategy.hpp"

class FCFSStrategy : public IDispatchStrategy
{
public:
    int selectElevator(const IRequest&               request,
                       const std::vector<Elevator*>& elevators,
                       const DispatchContext&        context) const override;
};
