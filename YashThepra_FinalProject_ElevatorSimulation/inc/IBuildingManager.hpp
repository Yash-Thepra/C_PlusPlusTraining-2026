#pragma once

#include "IBuilding.hpp"

#include <memory>
#include <string_view>

class IBuildingManager
{
public:
    virtual void       registerBuilding(std::unique_ptr<IBuilding> building) = 0;

    virtual void       shutdownAll()                                         = 0;
};
