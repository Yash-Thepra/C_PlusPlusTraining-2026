#pragma once

#include "IDispatchStrategy.hpp"

#include <memory>

class AdaptiveStrategy : public IDispatchStrategy
{
public:
    AdaptiveStrategy(const int minimumFloor, const int maximumFloor);

    int selectElevator(const IRequest&               request,
                       const std::vector<Elevator*>& elevators,
                       const DispatchContext&        context)  const override;

private:
    IDispatchStrategy& pick(const DispatchContext& context)    const;

    mutable IDispatchStrategy*         active{nullptr};
    std::unique_ptr<IDispatchStrategy> fcfs;
    std::unique_ptr<IDispatchStrategy> look;
    std::unique_ptr<IDispatchStrategy> scan;
};
