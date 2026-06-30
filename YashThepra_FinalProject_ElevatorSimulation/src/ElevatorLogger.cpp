#include "ElevatorLogger.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

ElevatorLogger::ElevatorLogger(std::ostream& stream)
    : stream{stream}
{
}

std::string ElevatorLogger::currentTimestamp() const
{
    const auto now         = std::chrono::system_clock::now();
    const auto realTime    = std::chrono::system_clock::to_time_t(now);
    const auto milliSecond = std::chrono::duration_cast<std::chrono::milliseconds>(
                             now.time_since_epoch()) % 1000;
    std::ostringstream stringStream;
    stringStream << std::put_time(std::localtime(&realTime), "%H:%M:%S")
                 << '.' << std::setfill('0') << std::setw(3) << milliSecond.count();
    return stringStream.str();
}

void ElevatorLogger::onFloorArrival(const int elevatorId, const int floor)
{
    std::lock_guard<std::mutex> lock{logMutex};
    stream << "[" << currentTimestamp() << "] "
             << "ELEV-" << elevatorId
             << " arrived at floor " << floor << "\n";
}

void ElevatorLogger::onRequestServiced(const int elevatorId, const int floor)
{
    std::lock_guard<std::mutex> lock{logMutex};
    stream << "[" << currentTimestamp() << "] "
             << "ELEV-" << elevatorId
             << " serviced floor " << floor << "\n";
}

void ElevatorLogger::onStateChanged(const int elevatorId, const ElevatorState state)
{
    std::lock_guard<std::mutex> lock{logMutex};
    stream << "[" << currentTimestamp() << "] "
             << "ELEV-" << elevatorId
             << " state -> " << stateToString(state) << "\n";
}

std::string ElevatorLogger::stateToString(const ElevatorState state) const
{
    switch (state)
    {
    case ElevatorState::Idle:          
         return "IDLE";
    case ElevatorState::MovingUp:      
         return "MOVING_UP";
    case ElevatorState::MovingDown:
         return "MOVING_DOWN";
    case ElevatorState::DoorOpen:  
         return "DOOR_OPEN";
    case ElevatorState::DoorClosed:
         return "DOOR_CLOSED";
    case ElevatorState::Maintenance: 
         return "MAINTENANCE";
    case ElevatorState::OutOfService: 
         return "OUT_OF_SERVICE";
    case ElevatorState::EmergencyStop: 
         return "EMERGENCY_STOP";
    default:                      
         return "UNKNOWN";
    }
}
