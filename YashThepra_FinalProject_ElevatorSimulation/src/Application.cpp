#include "Application.hpp"
#include "BuildingManager.hpp"
#include "Constant.hpp"
#include "StandardElevator.hpp"

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

Application::Application() : scheduler{ElevatorScheduler::getInstance()}
{
    using namespace Constant;
    setupDisplayPipe();
    printCommandInstructions();
    openDisplayStream();
    scheduler.startScheduler();

    const auto *adaptive = dynamic_cast<const AdaptiveStrategy *>(scheduler.getStrategy());
    building = std::make_unique<Building>("InTimeTec Tower", minimumBasementFloor, 
                                                             maximumFloor, 
                                                             &scheduler);
    building->initialize();
    auto *manager = building->getElevatorManager();
    manager->addElevator(std::make_unique<StandardElevator>(0, minimumBasementFloor, maximumFloor));
    manager->addElevator(std::make_unique<StandardElevator>(1, minimumBasementFloor, maximumFloor));

    logFile.open("elevator.log", std::ios::app);
    logger = std::make_unique<ElevatorLogger>(logFile);
    display = std::make_unique<DisplayPanel>(totalElevators, *displayStream);

    manager->addObserverToAll(logger.get());
    manager->addObserverToAll(display.get());

    manager->startAll();

    userInterfaceHandler = std::make_unique<UserInterfaceHandler>(*display, *displayStream);
    userInterfaceHandler->start();

    BuildingManager::getInstance().registerBuilding(std::move(building));

    inputHandler = std::make_unique<InputHandler>(
        manager,
        InputHandlerConfiguration{minimumBasementFloor, maximumFloor, totalElevators},
        [this]
        { requestShutdown(); });
    inputHandler->start();
}

Application::~Application()
{
    if (inputHandler)
    {
        inputHandler->stop();
    }
    if (userInterfaceHandler)
    {
        userInterfaceHandler->stop();
    }
    BuildingManager::getInstance().shutdownAll();
    scheduler.stopScheduler();
    if (fifoFd >= 0)
    {
        ::close(fifoFd);
    }
    if (fifoOk)
    {
        ::unlink(displayCatTerminalPipe);
    }
    std::cout << "\n\033[1m[INFO] Simulation stopped.\033[0m\n";
}

void Application::setupDisplayPipe()
{
    ::unlink(displayCatTerminalPipe);
    if (::mkfifo(displayCatTerminalPipe, 0666) != 0)
    {
        std::cerr << "[WARN] mkfifo failed — display goes to stdout.\n";
        fifoOk = false;
        return;
    }
    fifoOk = true;
}

void Application::openDisplayStream()
{
    displayStream = &std::cout;
    if (!fifoOk)
    {
        return;
    }
    fifoFd = ::open(displayCatTerminalPipe, O_RDWR | O_NONBLOCK);
    if (fifoFd < 0)
    {
        return; 
    }
    fifoBuffer = std::make_unique<OutputBufferHandler>(fifoFd);
    fifoStream = std::make_unique<std::ostream>(fifoBuffer.get());
    displayStream = fifoStream.get();
}

void Application::printCommandInstructions() const
{
    std::cout << "\033[1m\033[96m"
              << "╔══════════════════════════════════════════════════╗\n"
              << "║       ELEVATOR SIMULATION  —  STARTED            ║\n"
              << "╠══════════════════════════════════════════════════╣\n";
    if (fifoOk)
        std::cout << "║  Open a second terminal and run:                 ║\n"
                  << "║    cat /tmp/elevator_display                     ║\n";
    else
        std::cout << "║  Display output going to this terminal.          ║\n";
    std::cout << "╚══════════════════════════════════════════════════╝\n\033[0m\n";
}

void Application::requestShutdown()
{
    shutdownRequested.store(true, std::memory_order_release);
    shutdownConditionVariable.notify_all();
}

void Application::waitForShutdown()
{
    std::unique_lock<std::mutex> lock{shutdownMutex};
    shutdownConditionVariable.wait(lock, [this]
                      { return shutdownRequested.load(std::memory_order_acquire); });
}

void Application::run()
{
    waitForShutdown();
}
