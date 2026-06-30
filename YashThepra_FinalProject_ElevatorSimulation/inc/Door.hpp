#pragma once

#include "Constant.hpp"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

enum class DoorState
{
    Open,
    Closed,
    Opening,
    Closing,
    Blocked
};

class Door
{
public:
    using Duration = std::chrono::steady_clock::duration;

    Door(Duration openDuration = Constant::doorOpenDuration);

    ~Door();

    DoorState getState()     const;

    bool      isObstructed() const;

    void      close();

    void      open();

    void      setObstructed(const bool obstructed);

private:
    void autoCloseTimer();

    Duration                openDuration;
    mutable std::mutex      mutexUtility;
    std::condition_variable conditionVariable;
    std::thread             timerThread;

    DoorState               state = DoorState::Closed;

    std::atomic<bool>       obstructed   = false;
    std::atomic<bool>       timerRunning = false;
};
