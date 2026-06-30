#pragma once

#include "IScheduler.hpp"

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ElevatorScheduler : public IScheduler
{
public:
    static ElevatorScheduler& getInstance();

    ElevatorScheduler(const ElevatorScheduler&)            = delete;

    ElevatorScheduler& operator=(const ElevatorScheduler&) = delete;

    IDispatchStrategy* getStrategy()                                         const override;

    void               processNext()                                               override;

    void               registerElevator(Elevator* elevator)                        override;

    void               schedule(const IRequest& request)                           override;

    void               setStrategy(std::unique_ptr<IDispatchStrategy> strategy)    override;

    int                getPendingCount() const;

    void               startScheduler();

    void               stopScheduler();

private:
    ElevatorScheduler();
    
    ~ElevatorScheduler();

    void             schedulerLoop();

    DispatchContext  buildContext() const;

    struct RequestEntry
    {
        int                       targetElevatorId;
        std::unique_ptr<IRequest> request;
    };

    std::unique_ptr<IDispatchStrategy>  strategy;
    std::vector<Elevator*>              elevators;
    std::queue<RequestEntry>            dispatchQueue;
    mutable std::mutex                  elevatorMutex;
    mutable std::mutex                  queueMutex;
    std::condition_variable             conditionVariable;
    std::thread                         schedulerThread;
    std::atomic<bool>                   running = false;
};
