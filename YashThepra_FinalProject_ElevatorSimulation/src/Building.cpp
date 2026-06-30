#include "Building.hpp"

#include <stdexcept>

Building::Building(const std::string& name,
                   const int          minimumFloor, 
                   const int          maximumFloor, 
                   IScheduler*        scheduler)
    : name{std::move(name)}
    , minimumFloor{minimumFloor}
    , maximumFloor{maximumFloor}
    , elevatorManager{std::make_unique<ElevatorManager>(scheduler)}
{
    if (minimumFloor >= maximumFloor)
    {
        throw std::invalid_argument{"Building: minimumFloor must be less than maximumFloor"};
    }
    if (name.empty())
    {
        throw std::invalid_argument{"Building: name must not be empty"};
    }
}

void Building::buildFloors()
{
    floors.clear();
    for (int floor = minimumFloor; floor <= maximumFloor; ++floor)
    {
        const bool hasUp   = (floor < maximumFloor);
        const bool hasDown = (floor > minimumFloor);
        floors.push_back(std::make_unique<Floor>(floor, hasUp, hasDown));
    }
}

ElevatorManager* Building::getElevatorManager() const
{
    return elevatorManager.get();
}

Floor* Building::getFloor(const int floorNumber) const
{
    if (floorNumber < minimumFloor || floorNumber > maximumFloor)
    {
        throw std::out_of_range{"Building::getFloor: floor out of range"};
    }
    const int index = floorNumber - minimumFloor;
    return floors.at(static_cast<std::size_t>(index)).get();
}

std::string_view Building::getName() const
{
    return name;
}

void Building::initialize()
{
    buildFloors();
    wireFloorPanels();
}

void Building::wireFloorPanels()
{
    for (auto& floor : floors)
    {
        if (!floor)
        {
            continue;
        }
        auto* panel = floor->getPanel();
        if (panel == nullptr)
        {
            continue;
        }
        panel->setButtonCallback(
            [manager = elevatorManager.get()](int f, Direction direction) {
                manager->handleExternalRequest(f, direction);
            });
    }
}
