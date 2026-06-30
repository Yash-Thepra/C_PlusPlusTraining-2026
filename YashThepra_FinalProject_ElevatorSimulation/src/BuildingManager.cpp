#include "BuildingManager.hpp"
#include "ElevatorManager.hpp"

BuildingManager& BuildingManager::getInstance()
{
    static BuildingManager instance;
    return instance;
}

void BuildingManager::registerBuilding(std::unique_ptr<IBuilding> building)
{
    if (!building)
    {
        return;
    }
    std::lock_guard<std::mutex> lock{mutexUtility};
    const std::string key{building->getName()};
    buildings[key] = std::move(building);
}

void BuildingManager::shutdownAll()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& [name, building] : buildings)
    {
        if (building)
        {
            building->getElevatorManager()->stopAll();
        }
    }
}
