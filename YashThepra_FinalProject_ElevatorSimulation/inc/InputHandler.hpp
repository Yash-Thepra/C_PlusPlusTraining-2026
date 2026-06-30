#pragma once

#include "ElevatorManager.hpp"

#include <atomic>
#include <functional>
#include <string>
#include <thread>

struct InputHandlerConfiguration
{
    int minFloor;
    int maxFloor;
    int elevatorCount;
};

class InputHandler
{
public:
    using ShutdownCallback = std::function<void()>;

    InputHandler(ElevatorManager*                 manager,
                 const InputHandlerConfiguration& configuration,
                 ShutdownCallback                 onShutdown);

    ~InputHandler();

    void start();

    void stop();

private:
    bool handleClearCommand(const std::string& userInput);

    bool handleEmergencyCommand(const std::string& userInput);

    bool handleExternalCommand(const std::string& userInput);

    bool handleInternalCommand(const std::string& userInput);

    bool handleObstructCommand(const std::string& userInput);

    bool handleResumeCommand(const std::string& userInput);

    bool processCommand(const std::string& userInput);

    void inputLoop();

    void printHelp()                  const;

    bool isValidElevatorId(int id)    const;

    bool isValidFloor(int floor)      const;

    ElevatorManager*          manager;
    InputHandlerConfiguration configuration;
    ShutdownCallback          onShutdown;
    std::atomic<bool>         running = false;
    std::thread               threadUtility;
};
