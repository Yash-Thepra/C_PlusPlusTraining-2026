#pragma once

#include "IDispatchStrategy.hpp"

class SCANStrategy : public IDispatchStrategy
{
public:
    SCANStrategy(const int minimumFloor, const int maximumFloor);

    int selectElevator(const IRequest&               request,
                       const std::vector<Elevator*>& elevators,
                       const DispatchContext&        context) const override;

private:
    int computeCost(const Elevator& elevator, 
                    const int       targetFloor, 
                    const Direction requestDir) const;

    int minimumFloor;
    int maximumFloor;
};
