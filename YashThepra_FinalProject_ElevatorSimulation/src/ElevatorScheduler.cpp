#include "ElevatorScheduler.hpp"
#include <iostream>
#include "AdaptiveStrategy.hpp"
#include "Constant.hpp"
#include "Elevator.hpp"
#include "ExternalRequest.hpp"

#include <stdexcept>

ElevatorScheduler::ElevatorScheduler()
    : strategy{std::make_unique<AdaptiveStrategy>(
          Constant::minimumBasementFloor,
          Constant::maximumFloor)}
{
}

ElevatorScheduler::~ElevatorScheduler()
{
    stopScheduler();
}

ElevatorScheduler& ElevatorScheduler::getInstance()
{
    static ElevatorScheduler instance;
    return instance;
}

DispatchContext ElevatorScheduler::buildContext() const
{
    DispatchContext dispatchContext;
    {
        std::lock_guard<std::mutex> queueLock{queueMutex};
        dispatchContext.pendingQueueSize = dispatchQueue.size();
    }
    dispatchContext.totalElevators = elevators.size();
    dispatchContext.busyElevators  = 0;
    for (const auto* e : elevators)
    {
        if (e != nullptr && e->getState() != ElevatorState::Idle)
        {
            ++dispatchContext.busyElevators;
        }
    }
    return dispatchContext;
}

int ElevatorScheduler::getPendingCount() const
{
    std::lock_guard<std::mutex> lock{queueMutex};
    return dispatchQueue.size();
}

IDispatchStrategy* ElevatorScheduler::getStrategy() const
{
    std::lock_guard<std::mutex> lock{elevatorMutex};
    return strategy.get();
}

void ElevatorScheduler::processNext()
{
    std::unique_lock<std::mutex> queueLock{queueMutex};
    if (dispatchQueue.empty())
    {
        return;
    }
    auto entry = std::move(dispatchQueue.front());
    dispatchQueue.pop();
    queueLock.unlock();
    std::lock_guard<std::mutex> eLock{elevatorMutex};
    for (auto* elevator : elevators)
    {
        if (elevator != nullptr && elevator->getId() == entry.targetElevatorId)
        {
            elevator->addRequest(std::move(entry.request));
            return;
        }
    }
}

void ElevatorScheduler::registerElevator(Elevator* elevator)
{
    if (elevator == nullptr)
    {
        return;
    }
    std::lock_guard<std::mutex> lock{elevatorMutex};
    elevators.push_back(elevator);
}

void ElevatorScheduler::schedule(const IRequest& request)
{
    std::lock_guard<std::mutex> eLock{elevatorMutex};
    if (elevators.empty() || strategy == nullptr)
    {
        return;
    }
    const DispatchContext dispatchContext = buildContext();
    const int             targetId        = strategy->selectElevator(request, 
                                                                     elevators, 
                                                                     dispatchContext);
    auto clone = std::make_unique<ExternalRequest>(
        request.getFloor(),
        request.getDirection(),
        request.getId());
    {
        std::lock_guard<std::mutex> queueLock{queueMutex};
        RequestEntry entry;
        entry.targetElevatorId = targetId;
        entry.request          = std::move(clone);
        dispatchQueue.push(std::move(entry));
    }
    conditionVariable.notify_one();
}

void ElevatorScheduler::setStrategy(std::unique_ptr<IDispatchStrategy> dispatchStrategy)
{
    if (!dispatchStrategy)
    {
        throw std::invalid_argument{"ElevatorScheduler: strategy must not be null"};
    }
    std::lock_guard<std::mutex> lock{elevatorMutex};
    strategy = std::move(dispatchStrategy);
}

void ElevatorScheduler::schedulerLoop()
{
    while (running.load(std::memory_order_acquire))
    {
        std::unique_lock<std::mutex> lock{queueMutex};
        conditionVariable.wait_for(lock, Constant::schedulerTickInterval, [this] {
            return !dispatchQueue.empty() ||
                   !running.load(std::memory_order_acquire);
        });
        lock.unlock();
        processNext();
    }
}

void ElevatorScheduler::startScheduler()
{
    if (running.exchange(true, std::memory_order_acq_rel))
    {
        return;
    }
    schedulerThread = std::thread{&ElevatorScheduler::schedulerLoop, this};
}

void ElevatorScheduler::stopScheduler()
{
    running.store(false, std::memory_order_release);
    conditionVariable.notify_all();
    if (schedulerThread.joinable())
    {
        schedulerThread.join();
    }
}
