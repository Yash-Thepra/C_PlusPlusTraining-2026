#include "FloorPanel.hpp"

FloorPanel::FloorPanel(const int floorNumber)
    : floorNumber{floorNumber}
{
}

void FloorPanel::extinguish(const Direction direction)
{
    if (direction == Direction::Up)
    {
        upLit.store(false, std::memory_order_release);
    }
    else if (direction == Direction::Down)
    {
        downLit.store(false, std::memory_order_release);
    }
}

int FloorPanel::getFloorNumber() const
{
    return floorNumber;
}

void FloorPanel::illuminate(const Direction direction)
{
    if (direction == Direction::Up)
    {
        upLit.store(true, std::memory_order_release);
    }
    else if (direction == Direction::Down)
    {
        downLit.store(true, std::memory_order_release);
    }
}

bool FloorPanel::isDownLit() const
{
    return downLit.load(std::memory_order_acquire);
}

bool FloorPanel::isUpLit() const
{
    return upLit.load(std::memory_order_acquire);
}

void FloorPanel::pressDown()
{
    illuminate(Direction::Down);
    if (callback)
    {
        callback(floorNumber, Direction::Down);
    }
}

void FloorPanel::pressUp()
{
    illuminate(Direction::Up);
    if (callback)
    {
        callback(floorNumber, Direction::Up);
    }
}

void FloorPanel::setButtonCallback(ButtonCallback callback)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    this->callback = std::move(callback);
}
