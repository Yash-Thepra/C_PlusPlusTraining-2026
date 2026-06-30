#pragma once

#include "IBuildingManager.hpp"

#include <mutex>
#include <string>
#include <unordered_map>

class BuildingManager : public IBuildingManager
{
public:
    static BuildingManager& getInstance();

    BuildingManager(const BuildingManager&)            = delete;

    BuildingManager& operator=(const BuildingManager&) = delete;
    
    void       registerBuilding(std::unique_ptr<IBuilding> building) override;
    void       shutdownAll()                                         override;

private:
    BuildingManager() {};

    ~BuildingManager() {};

    std::unordered_map<std::string, std::unique_ptr<IBuilding>> buildings;
    mutable std::mutex                                          mutexUtility;
};
