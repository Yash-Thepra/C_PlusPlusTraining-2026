#pragma once

#include <gmock/gmock.h>

#include "IBuilding.hpp"

class MockBuilding : public IBuilding
{
public:
    MOCK_METHOD(
        ElevatorManager*,
        getElevatorManager,
        (),
        (const, override));

    MOCK_METHOD(
        Floor*,
        getFloor,
        (int),
        (const, override));

    MOCK_METHOD(
        std::string_view,
        getName,
        (),
        (const, override));

    MOCK_METHOD(
        void,
        initialize,
        (),
        (override));
};
