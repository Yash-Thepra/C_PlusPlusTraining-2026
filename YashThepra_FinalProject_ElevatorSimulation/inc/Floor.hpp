#pragma once

#include "FloorPanel.hpp"

#include <memory>
#include <string>

class Floor
{
public:
    Floor(const int floorNumber, const bool hasUpButton, const bool hasDownButton);

    int         getFloorNumber() const;

    std::string getLabel()       const;

    FloorPanel* getPanel();

    bool        hasDownButton()  const;

    bool        hasUpButton()    const;

    void        pressDown();

    void        pressUp();

private:
    std::string computeLabel() const;

    int                         floorNumber;
    bool                        checkDownButton;
    bool                        checkUpButton;
    std::string                 label;
    std::unique_ptr<FloorPanel> panel;
};
