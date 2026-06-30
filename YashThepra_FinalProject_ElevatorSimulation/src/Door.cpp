#include "Door.hpp"

Door::Door(Duration openDuration)
    : openDuration{openDuration}
{
}

Door::~Door()
{
    timerRunning.store(false, std::memory_order_release);
    conditionVariable.notify_all();
    if (timerThread.joinable())
    {
        timerThread.join();
    }
}

DoorState Door::getState() const
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    return state;
}

bool Door::isObstructed() const
{
    return obstructed.load(std::memory_order_acquire);
}

void Door::close()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    if (state == DoorState::Closed || state == DoorState::Closing)
    {
        return;
    }
    if (obstructed.load(std::memory_order_acquire))
    {
        state = DoorState::Blocked;
        return;
    }
    state = DoorState::Closing;
    std::this_thread::sleep_for(std::chrono::milliseconds{300});
    state = DoorState::Closed;
}

void Door::open()
{
    {
        std::lock_guard<std::mutex> lock{mutexUtility};
        if (state == DoorState::Open || state == DoorState::Opening)
        {
            return;
        }
        state = DoorState::Opening;
        std::this_thread::sleep_for(std::chrono::milliseconds{300});
        state = DoorState::Open;
    }
    if (!timerRunning.exchange(true, std::memory_order_acq_rel))
    {
        if (timerThread.joinable())
        {
            timerThread.join();
        }
        timerThread = std::thread{&Door::autoCloseTimer, this};
    }
}

void Door::setObstructed(bool isObstructed)
{
    obstructed.store(isObstructed, std::memory_order_release);
    if (!isObstructed)
    {
        conditionVariable.notify_one();
    }
}

void Door::autoCloseTimer()
{
    std::unique_lock<std::mutex> lock{mutexUtility};
    conditionVariable.wait_for(lock, openDuration, [this] {
        return !timerRunning.load(std::memory_order_acquire);
    });
    if (!timerRunning.load(std::memory_order_acquire))
    {
        return;
    }
    while (obstructed.load(std::memory_order_acquire) &&
           timerRunning.load(std::memory_order_acquire))
    {
        lock.unlock();
        std::this_thread::sleep_for(Constant::doorCloseRetryDelay);
        lock.lock();
    }
    if (!timerRunning.load(std::memory_order_acquire))
    {
        return;
    }
    state = DoorState::Closing;
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds{300});
    lock.lock();
    state = DoorState::Closed;
    timerRunning.store(false, std::memory_order_release);
}
