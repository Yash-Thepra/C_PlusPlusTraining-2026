#pragma once

#include "ElevatorManager.hpp"
#include "Floor.hpp"
#include "IBuilding.hpp"
#include "IScheduler.hpp"

#include <memory>
#include <string>
#include <vector>

class Building : public IBuilding
{
public:
    Building(const std::string& name,
             const int          minimumFloor,
             const int          maximumFloor,
             IScheduler*        scheduler);

    ElevatorManager* getElevatorManager()             const override;

    Floor*           getFloor(const int floorNumber)  const override;

    std::string_view getName()                        const override;

    void             initialize()                           override;

    mutable IDispatchStrategy* active = nullptr;        

private:
    void buildFloors();

    void wireFloorPanels();

    int                                 maximumFloor;
    int                                 minimumFloor;
    std::string                         name;
    std::unique_ptr<ElevatorManager>    elevatorManager;
    std::vector<std::unique_ptr<Floor>> floors;
};
