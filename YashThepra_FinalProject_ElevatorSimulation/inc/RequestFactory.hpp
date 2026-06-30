#pragma once

#include "IRequest.hpp"

#include <memory>

class RequestFactory
{
public:
    RequestFactory()  = delete;
    
    ~RequestFactory() = delete;

    static std::unique_ptr<IRequest> createExternal(const int floor, const Direction direction);

    static std::unique_ptr<IRequest> createInternal(const int elevatorId, const int destinationFloor);

private:
    static int nextId();
};
