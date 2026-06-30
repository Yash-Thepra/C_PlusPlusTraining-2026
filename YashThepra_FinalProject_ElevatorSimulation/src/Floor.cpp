#include "Floor.hpp"
#include "Constant.hpp"

Floor::Floor(const int floorNumber, const bool checkUpButton, const bool checkDownButton)
    : floorNumber{floorNumber}
    , checkDownButton{checkDownButton}
    , checkUpButton{checkUpButton}
    , label{computeLabel()}
    , panel{std::make_unique<FloorPanel>(floorNumber)}
{
}

std::string Floor::computeLabel() const
{
    std::string result;
    if (floorNumber == Constant::groundFloor)
    {
        result = Constant::groundLabel;
    }
    else if (floorNumber < 0)
    {
        result = std::string{Constant::basementLabel} +
                 std::to_string(-floorNumber);
    }
    else
    {
        result = std::to_string(floorNumber);
    }
    return result;
}

int Floor::getFloorNumber() const
{
    return floorNumber;
}

std::string Floor::getLabel() const
{
    return label;
}

FloorPanel* Floor::getPanel()
{
    return panel.get();
}

bool Floor::hasDownButton() const
{
    return checkDownButton;
}

bool Floor::hasUpButton() const
{
    return checkUpButton;
}

void Floor::pressDown()
{
    if (!checkDownButton)
    {
        return;
    }
    panel->pressDown();
}

void Floor::pressUp()
{
    if (!checkUpButton)
    {
        return;
    }
    panel->pressUp();
}
