#pragma once

#include "IRequest.hpp"

#include <atomic>
#include <functional>
#include <mutex>

class FloorPanel
{
public:
    FloorPanel(const int floorNumber);

    int  getFloorNumber() const;

    bool isDownLit()      const;

    bool isUpLit()        const;

    void extinguish(const Direction direction);

    void illuminate(const Direction direction);

    void pressDown();

    void pressUp();

    using ButtonCallback = std::function<void(int floor, Direction direction)>;

    void setButtonCallback(const ButtonCallback callback);

private:
    ButtonCallback     callback;
    int                floorNumber;
    mutable std::mutex mutexUtility;
    std::atomic<bool>  downLit = false;
    std::atomic<bool>  upLit   = false;
};
