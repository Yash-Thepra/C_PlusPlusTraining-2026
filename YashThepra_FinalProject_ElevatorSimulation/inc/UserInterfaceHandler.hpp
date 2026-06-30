#pragma once

#include "DisplayPanel.hpp"

#include <atomic>
#include <ostream>
#include <thread>

class UserInterfaceHandler
{
public:
    UserInterfaceHandler(const DisplayPanel& displayPanel, std::ostream& out);

    ~UserInterfaceHandler();

    void start();
    void stop();

private:
    void clearStream() const;

    void renderLoop();

    const DisplayPanel& displayPanel;
    std::atomic<bool>   running = false;
    std::ostream&       outputStream;
    std::thread         threadUtility;
};
