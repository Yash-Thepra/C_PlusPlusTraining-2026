#include "UserInterfaceHandler.hpp"
#include "Constant.hpp"

#include <thread>

UserInterfaceHandler::UserInterfaceHandler(const DisplayPanel& displayPanel, 
                                                 std::ostream& outputStream)
    : displayPanel{displayPanel}
    , outputStream{outputStream}
{
}

UserInterfaceHandler::~UserInterfaceHandler()
{
    stop();
}

void UserInterfaceHandler::clearStream() const
{
    outputStream << "\033[3J\033[2J\033[H";
}

void UserInterfaceHandler::renderLoop()
{
    while (running.load(std::memory_order_acquire))
    {
        clearStream();
        displayPanel.render();
        std::this_thread::sleep_for(Constant::userInterfaceRefreshInterval);
    }
}

void UserInterfaceHandler::start()
{
    if (running.exchange(true, std::memory_order_acq_rel))
    {
        return;
    }
    threadUtility = std::thread{&UserInterfaceHandler::renderLoop, this};
}

void UserInterfaceHandler::stop()
{
    running.store(false, std::memory_order_release);
    if (threadUtility.joinable())
    {
        threadUtility.join();
    }
}
