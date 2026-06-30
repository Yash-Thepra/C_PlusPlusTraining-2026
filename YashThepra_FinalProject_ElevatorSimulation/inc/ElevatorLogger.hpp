#pragma once

#include "IObserver.hpp"

#include <mutex>
#include <ostream>
#include <string>

class ElevatorLogger : public IObserver
{
public:
    ElevatorLogger(std::ostream& stream);

    void onFloorArrival(const int elevatorId, const int floor)              override;

    void onRequestServiced(const int elevatorId, const int floor)           override;

    void onStateChanged(const int elevatorId, const ElevatorState state)    override;

private:
    std::string currentTimestamp()                       const;

    std::string stateToString(const ElevatorState state) const;

    std::ostream&      stream;
    mutable std::mutex logMutex;
};
