#include "DisplayPanel.hpp"
#include "Constant.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

const char* DisplayPanel::RESET  = "\033[0m";
const char* DisplayPanel::BOLD   = "\033[1m";
const char* DisplayPanel::DIM    = "\033[2m";
const char* DisplayPanel::RED    = "\033[91m";
const char* DisplayPanel::GREEN  = "\033[92m";
const char* DisplayPanel::YELLOW = "\033[93m";
const char* DisplayPanel::CYAN   = "\033[96m";
const char* DisplayPanel::WHITE  = "\033[97m";

DisplayPanel::DisplayPanel(const int elevatorCount, std::ostream& outputStream)
    : outputStream{outputStream}
    , elevatorCount{elevatorCount}
{
    for (int i = 0; i < elevatorCount; ++i)
    {
        currentFloor[i] = Constant::groundFloor;
        directionMap[i] = Direction::None;
        stateMap[i]     = ElevatorState::Idle;
    }
}

void DisplayPanel::onFloorArrival(const int elevatorId, const int floor)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    currentFloor[elevatorId] = floor;
    pushEvent("E" + std::to_string(elevatorId) +
              " arrived  floor " + floorLabel(floor));
}

void DisplayPanel::onRequestServiced(const int elevatorId, const int floor)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    currentFloor[elevatorId] = floor;
    pushEvent("E" + std::to_string(elevatorId) +
              " serviced floor " + floorLabel(floor));
}

void DisplayPanel::onStateChanged(const int elevatorId, const ElevatorState state)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    stateMap[elevatorId] = state;
    if (state == ElevatorState::MovingUp)
    {
        directionMap[elevatorId] = Direction::Up;
    }
    else if (state == ElevatorState::MovingDown)
    {
        directionMap[elevatorId] = Direction::Down;
    }
    else if (state == ElevatorState::Idle)
    {
        directionMap[elevatorId] = Direction::None;
    }
}

void DisplayPanel::pushEvent(const std::string& message)
{
    eventLog.push_back(message);
    if (static_cast<int>(eventLog.size()) > maximumLogLines)
    {
        eventLog.erase(eventLog.begin());
    }
}

std::string DisplayPanel::padRight(std::string state, const int width) const
{
    if (static_cast<int>(state.size()) < width)
    {
        state.append(static_cast<std::size_t>(width - static_cast<int>(state.size())), ' ');
    }
    return state;
}

std::string DisplayPanel::floorLabel(const int floor) const
{
    std::string temp = "";
    if (floor == Constant::groundFloor) 
    {
        temp = "G ";
    }
    else if (floor < 0)
    {
        temp = "B" + std::to_string(-floor);
    }
    else
    {
        temp = std::to_string(floor) + " ";
    }
    return temp;
}

std::string DisplayPanel::directionPoint(const Direction direction) const
{
    switch (direction)
    {
    case Direction::Up:   
         return std::string{GREEN}  + " ▲ " + RESET;
    case Direction::Down: 
         return std::string{YELLOW} + " ▼ " + RESET;
    default:              
         return std::string{DIM}    + " — " + RESET;
    }
}

std::string DisplayPanel::stateLabel(const ElevatorState state) const
{
    switch (state)
    {
    case ElevatorState::Idle:          
         return "IDLE";
    case ElevatorState::MovingUp:      
         return "MOVING UP";
    case ElevatorState::MovingDown:    
         return "MOVING DOWN";
    case ElevatorState::DoorOpen:      
         return "DOOR OPEN";
    case ElevatorState::DoorClosed:    
        return "DOOR CLOSED";
    case ElevatorState::Maintenance:   
         return "MAINTENANCE";
    case ElevatorState::OutOfService:  
         return "OUT OF SERVICE";
    case ElevatorState::EmergencyStop: 
         return "EMERGENCY STOP";
    default:                           
         return "UNKNOWN";
    }
}

std::string DisplayPanel::stateColor(const ElevatorState state) const
{
    switch (state)
    {
    case ElevatorState::MovingUp:
    case ElevatorState::MovingDown:    
         return GREEN;
    case ElevatorState::DoorOpen:      
         return CYAN;
    case ElevatorState::EmergencyStop: 
         return RED;
    case ElevatorState::OutOfService:
    case ElevatorState::Maintenance:   
         return YELLOW;
    default:
         return WHITE;
    }
}

void DisplayPanel::render() const
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    const int minimumFloor = Constant::minimumBasementFloor;
    const int maximumFloor = Constant::maximumFloor;
    std::ostringstream buffer;
    buffer << BOLD << WHITE << "  Floor ";
    for (int e = 0; e < elevatorCount; ++e)
    {
        buffer << "│  Elevator " << e << "         ";
    }
    buffer << "│\n" << RESET;
    buffer << "  ──────";
    for (int e = 0; e < elevatorCount; ++e)
    {
        buffer << "┼─────────────────────";
    }
    buffer << "┤\n";
    for (int floor = maximumFloor ; floor >= minimumFloor; --floor)
    {
        std::string lbl = floorLabel(floor);
        buffer << BOLD << (floor == 0 ? GREEN : WHITE)
            << "  " << std::setw(4) << std::left << lbl << RESET;
        for (int e = 0; e < elevatorCount; ++e)
        {
            buffer << "  │  ";
            const int   elevatorFloor = currentFloor.at(e);
            const auto  elevatorState = stateMap.at(e);
            const auto  elevatorDirection = directionMap.at(e);
            if (elevatorFloor == floor)
            {
                buffer << stateColor(elevatorState) << BOLD
                    << "[ E" << e << " ]" << RESET
                    << directionPoint(elevatorDirection)
                    << "        ";
            }
            else
            {
                buffer << DIM << "  ·  " << RESET << "            ";
            }
        }
        buffer << "  │\n";
    }
    buffer << "  ──────";
    for (int e = 0; e < elevatorCount; ++e)
    {
        buffer << "┴─────────────────────";
    }
    buffer << "┘\n\n";
    buffer << BOLD << WHITE << "  STATUS:\n" << RESET;
    for (int e = 0; e < elevatorCount; ++e)
    {
        const auto elevatorState = stateMap.at(e);
        const int  elevatorFloor = currentFloor.at(e);
        const auto elevatorDirection = directionMap.at(e);
        buffer << "  Elevator " << e << " │ "
            << stateColor(elevatorState) << BOLD << padRight(stateLabel(elevatorState), 16) << RESET
            << " │ Floor: " << BOLD << floorLabel(elevatorFloor) << RESET
            << " │ " << directionPoint(elevatorDirection) << "\n";
    }
    buffer << "\n" << BOLD << WHITE << "  EVENTS:\n" << RESET;
    if (eventLog.empty())
    {
        buffer << DIM << "  (waiting for requests...)\n" << RESET;
    }
    else
    {
        {
        for (const auto& ev : eventLog)
            buffer << DIM << "  › " << RESET << ev << "\n";
        }
    }
    buffer << "\n";
    outputStream << buffer.str();
    outputStream.flush();
}
