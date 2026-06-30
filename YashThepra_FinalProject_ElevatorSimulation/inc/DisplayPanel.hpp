#pragma once

#include "IObserver.hpp"
#include "IRequest.hpp"

#include <mutex>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

class DisplayPanel : public IObserver
{
public:
    DisplayPanel(const int elevatorCount, std::ostream& outputStream);

    void onFloorArrival(const int elevatorId, const int floor)     override;

    void onRequestServiced(const int elevatorId, const int floor)  override;

    void onStateChanged(const int elevatorId, ElevatorState state) override;

    void render() const;

    void pushEvent(const std::string& message);

private:
    std::string directionPoint(Direction direction)             const;

    std::string floorLabel(const int floor)                     const;

    std::string stateLabel(ElevatorState state)                 const;

    std::string stateColor(ElevatorState state)                 const;

    std::string padRight(std::string state, const int width)        const;

    static const char* BOLD;
    static const char* CYAN;
    static const char* DIM;
    static const char* GREEN;
    static const char* RED;
    static const char* RESET;
    static const char* WHITE;
    static const char* YELLOW;

    int                                    elevatorCount;
    mutable std::mutex                     mutexUtility;
    std::ostream&                          outputStream;
    std::unordered_map<int, Direction>     directionMap;
    std::unordered_map<int, ElevatorState> stateMap;
    std::unordered_map<int, int>           currentFloor;
    std::vector<std::string>               eventLog;

    static constexpr int                   columnWidth    = 28;
    static constexpr int                   maximumLogLines = 8;
};
