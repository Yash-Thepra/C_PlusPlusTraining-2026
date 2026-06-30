#pragma once

#include "IDispatchStrategy.hpp"

class LOOKStrategy : public IDispatchStrategy
{
public:
    int selectElevator(const IRequest&               request,
                       const std::vector<Elevator*>& elevators,
                       const DispatchContext&        context) const override;

private:
    int computeCost(const Elevator& elevator, 
                    const int       targetFloor, 
                    const Direction requestDir) const;
};
