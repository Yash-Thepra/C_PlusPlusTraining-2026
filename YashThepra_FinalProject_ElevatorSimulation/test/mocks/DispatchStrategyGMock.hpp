#pragma once

#include <gmock/gmock.h>

#include "IDispatchStrategy.hpp"

class DispatchStrategyGMock : public IDispatchStrategy
{
public:
    MOCK_METHOD(
        int,
        selectElevator,
        (const IRequest&,
         const std::vector<Elevator*>&,
         const DispatchContext&),
        (const, override));
};
