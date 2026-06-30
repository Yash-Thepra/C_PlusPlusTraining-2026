#pragma once

#include <memory>
#include <string_view>

class ElevatorManager;

class Floor;           

class IBuilding
{
public:
    virtual ~IBuilding() {};

    virtual ElevatorManager* getElevatorManager()            const = 0;

    virtual Floor*           getFloor(const int floorNumber) const = 0;

    virtual std::string_view getName()                       const = 0;

    virtual void             initialize()                          = 0;
};
