#include "InputHandler.hpp"
#include "Constant.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

InputHandler::InputHandler(ElevatorManager*                 manager,
                           const InputHandlerConfiguration& configuration,
                           ShutdownCallback                 onShutdown)
    : manager{manager}
    , configuration{configuration}
    , onShutdown{std::move(onShutdown)}
{
    if (manager == nullptr)
    {
        throw std::invalid_argument{"InputHandler: manager must not be null"};
    }
}

InputHandler::~InputHandler()
{
    stop();
}

bool InputHandler::handleEmergencyCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    stringStream >> token;
    int  elevatorId;
    bool result = true; 
    if (stringStream >> elevatorId)
    {
        if (!isValidElevatorId(elevatorId))
        {
            std::cout << "  [!] Elevator ID " << elevatorId
                      << " out of range [0, " << (configuration.elevatorCount - 1) << "]\n";
            result = false;
        }
        else
        {
            manager->triggerEmergency(elevatorId);
            std::cout << "  [EMERGENCY] Elevator " << elevatorId
                      << " stopped — abandoning queue, returning to refuge floor.\n";
        }
    }
    else
    {
        manager->triggerEmergencyAll();
        std::cout << "  [EMERGENCY] ALL elevators stopped — abandoning queues, "
                     "returning to refuge floor.\n";
    }
    return result;
}

bool InputHandler::handleResumeCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    stringStream >> token; 
    int  elevatorId;
    bool result = true;
    if (stringStream >> elevatorId)
    {
        if (!isValidElevatorId(elevatorId))
        {
            std::cout << "  [!] Elevator ID " << elevatorId
                      << " out of range [0, " << (configuration.elevatorCount - 1) << "]\n";
            result = false;
        }
        else 
        {
            manager->resumeService(elevatorId);
            std::cout << "  Elevator " << elevatorId << " back in service.\n";
        }
    }
    else
    {
        manager->resumeServiceAll();
        std::cout << "  ALL elevators back in service.\n";
    }
    return result;
}

bool InputHandler::handleObstructCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    int                elevatorId;
    bool               result = true;
    stringStream >> token >> elevatorId;
    if (stringStream.fail() || !isValidElevatorId(elevatorId))
    {
        std::cout << "  [!] Usage: obstruct <elevatorId>\n";
        result = false;
    }
    else
    {
        const bool isObstructed = manager->obstructDoor(elevatorId);
        std::cout << (isObstructed
            ? "  Elevator " + std::to_string(elevatorId) + " doorway obstructed.\n"
            : "  [!] Elevator " + std::to_string(elevatorId) + " is not idle with doors open — cannot obstruct.\n");
            result = isObstructed;
    }
    return result;
}

bool InputHandler::handleClearCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    int                elevatorId;
    bool               result = true;
    stringStream >> token >> elevatorId;
    if (stringStream.fail() || !isValidElevatorId(elevatorId))
    {
        std::cout << "  [!] Usage: clear <elevatorId>\n";
        result = false;
    }
    else 
    {
        const bool isCleared = manager->clearObstruction(elevatorId);
        std::cout << (isCleared
            ? "  [OK] Elevator " + std::to_string(elevatorId) + " obstruction cleared.\n"
            : "  [!] Elevator " + std::to_string(elevatorId) + " was not obstructed.\n");
        result = isCleared;
    }
    return result;
}

bool InputHandler::handleExternalCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    char               directionChar;
    int                floor;
    bool               result = true;
    stringStream >> token >> floor >> directionChar;
    if (stringStream.fail())
    {
        std::cout << "  [!] Usage: ext <floor> <U|D>\n";
        result = false;
    }
    else if (!isValidFloor(floor))
    {
        std::cout << "  [!] Floor " << floor << " out of range ["
                  << configuration.minFloor << ", " << configuration.maxFloor << "]\n";
        result = false;
    }
    else
    {
        Direction direction{Direction::None};
        if (directionChar == 'U' || directionChar == 'u')
        {
            if (floor == configuration.maxFloor)
            {
                std::cout << "  [!] Cannot go UP from top floor\n";
                result = false;
            }
            else
            {
                direction = Direction::Up;
            }
        }
        else if (directionChar == 'D' || directionChar == 'd')
        {
            if (floor == configuration.minFloor)
            {
                std::cout << "  [!] Cannot go DOWN from bottom floor\n";
                result = false;
            }
            else
            {
                direction = Direction::Down;
            }
        }
        else
        {
            std::cout << "  [!] Direction must be U (up) or D (down)\n";
            result = false;
        }
        if(result)
        {
            manager->handleExternalRequest(floor, direction);
            std::cout << "  [OK] External request: floor " << floor
                      << " direction " << (direction == Direction::Up ? "UP" : "DOWN") << "\n";
        }
    }
    return result;
}

bool InputHandler::handleInternalCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        token;
    int                elevatorId;
    int                floor;
    bool               result = true;
    stringStream >> token >> elevatorId >> floor;
    if (stringStream.fail())
    {
        std::cout << "  [!] Usage: int <elevatorId> <floor>\n";
        result = false;
    }
    else if (!isValidElevatorId(elevatorId))
    {
        std::cout << "  [!] Elevator ID " << elevatorId
                  << " out of range [0, " << (configuration.elevatorCount - 1) << "]\n";
        result = false;
    }
    else if (!isValidFloor(floor))
    {
        std::cout << "  [!] Floor " << floor << " out of range ["
                  << configuration.minFloor << ", " << configuration.maxFloor << "]\n";
        result = false;
    }
    else
    {
        manager->handleInternalRequest(elevatorId, floor);
        std::cout << "  [OK] Internal request: elevator " << elevatorId
                  << " -> floor " << floor << "\n";
    }
    return result;
}

void InputHandler::inputLoop()
{
    printHelp();
    std::string line;
    while (running.load(std::memory_order_acquire))
    {
        std::cout << "\n> ";
        std::cout.flush();
        if (!std::getline(std::cin, line))
        {
            break;
        }
        if (line.empty())
        {
            continue;
        }
        if (!processCommand(line))
        {
            break;
        }
    }
}

bool InputHandler::isValidElevatorId(const int id) const
{
    return id >= 0 && id < configuration.elevatorCount;
}

bool InputHandler::isValidFloor(const int floor) const
{
    return floor >= configuration.minFloor && floor <= configuration.maxFloor;
}

void InputHandler::printHelp() const
{
    std::cout << "\n╔══════════════════════════════════════════════╗\n";
    std::cout << "║        ELEVATOR SIMULATION - COMMANDS        ║\n";
    std::cout << "╠══════════════════════════════════════════════╣\n";
    std::cout << "║  ext <floor> <U|D>  Hall button press        ║\n";
    std::cout << "║  int <id> <floor>   Cabin button press       ║\n";
    std::cout << "║  emg                Emergency — ALL elevators║\n";
    std::cout << "║  emg <id>           Emergency — ONE elevator ║\n";
    std::cout << "║  resume             Resume — ALL elevators   ║\n";
    std::cout << "║  resume <id>        Resume — ONE elevator    ║\n";
    std::cout << "║  obstruct <id>      Block doorway (testing)  ║\n";
    std::cout << "║  clear <id>         Clear door obstruction   ║\n";
    std::cout << "║  help               Show this menu           ║\n";
    std::cout << "║  exit               Graceful shutdown        ║\n";
    std::cout << "╠══════════════════════════════════════════════╣\n";
    std::cout << "║  Floors: B2=" << configuration.minFloor
              << "  B1=-1  G=0  1-" << configuration.maxFloor << "              ║\n";
    std::cout << "║  Elevators: 0 to " << (configuration.elevatorCount - 1)
              << "                           ║\n";
    std::cout << "╚══════════════════════════════════════════════╝\n";
}

bool InputHandler::processCommand(const std::string& line)
{
    std::istringstream stringStream{line};
    std::string        command;
    bool               result = true;
    stringStream >> command;
    if (command == "exit")
    {
        std::cout << "  Shutting down...\n";
        running.store(false, std::memory_order_release);
        if (onShutdown)
        {
            onShutdown();
        }
        result = false;
    }
    else if (command == "help")
    {
        printHelp();
    }
    else if (command == "ext")
    {
        handleExternalCommand(line);
    }
    else if (command == "int")
    {
        handleInternalCommand(line);
    }
    else if (command == "emg")
    {
        handleEmergencyCommand(line);
    }
    else if (command == "resume")
    {
        handleResumeCommand(line);
    }
    else if (command == "obstruct")
    {
        handleObstructCommand(line);
    }
    else if (command == "clear")
    {
        handleClearCommand(line);
    }
    else 
    {
        std::cout << "  [!] Unknown command: '" << command << "'Type 'help'.\n";
    }
    return result;
}

void InputHandler::start()
{
    if (running.exchange(true, std::memory_order_acq_rel))
    {
        return;
    }
    threadUtility = std::thread{&InputHandler::inputLoop, this};
}

void InputHandler::stop()
{
    running.store(false, std::memory_order_release);
    if (threadUtility.joinable())
    {
        threadUtility.detach();
    }
}
