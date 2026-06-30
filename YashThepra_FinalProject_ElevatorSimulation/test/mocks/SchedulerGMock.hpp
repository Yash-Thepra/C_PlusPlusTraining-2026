#pragma once

#include <gmock/gmock.h>

#include "IScheduler.hpp"

class SchedulerGMock : public IScheduler
{
public:
    MOCK_METHOD(
        IDispatchStrategy*,
        getStrategy,
        (),
        (const, override));

    MOCK_METHOD(
        void,
        processNext,
        (),
        (override));

    MOCK_METHOD(
        void,
        registerElevator,
        (Elevator*),
        (override));

    MOCK_METHOD(
        void,
        schedule,
        (const IRequest&),
        (override));

    MOCK_METHOD(
        void,
        setStrategy,
        (std::unique_ptr<IDispatchStrategy>),
        (override));
};
