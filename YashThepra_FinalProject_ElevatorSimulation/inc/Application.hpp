#pragma once

#include "AdaptiveStrategy.hpp"
#include "Building.hpp"
#include "DisplayPanel.hpp"
#include "ElevatorLogger.hpp"
#include "ElevatorScheduler.hpp"
#include "InputHandler.hpp"
#include "OutputBufferHandler.hpp"
#include "UserInterfaceHandler.hpp"

#include <atomic>
#include <condition_variable>
#include <fstream>
#include <memory>
#include <mutex>
#include <ostream>

class Application
{
public:
    Application();

    ~Application();

    void run();

private:
    void openDisplayStream();

    void printCommandInstructions() const;

    void requestShutdown();

    void setupDisplayPipe();

    void waitForShutdown();

    static constexpr const char* displayCatTerminalPipe = "/tmp/elevator_display";

    bool                                  fifoOk = false;
    ElevatorScheduler&                    scheduler;
    int                                   fifoFd = -1;
    std::atomic<bool>                     shutdownRequested = false;
    std::condition_variable               shutdownConditionVariable;
    std::mutex                            shutdownMutex;
    std::ofstream                         logFile;
    std::ostream*                         displayStream = nullptr;
    std::unique_ptr<Building>             building;
    std::unique_ptr<DisplayPanel>         display;
    std::unique_ptr<ElevatorLogger>       logger;
    std::unique_ptr<InputHandler>         inputHandler;
    std::unique_ptr<OutputBufferHandler>  fifoBuffer;
    std::unique_ptr<std::ostream>         fifoStream;
    std::unique_ptr<UserInterfaceHandler> userInterfaceHandler;
};
