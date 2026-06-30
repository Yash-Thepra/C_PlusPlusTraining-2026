#pragma once

#include "Constant.hpp"
#include "Door.hpp"
#include "ExternalRequestManager.hpp"
#include "IObserver.hpp"
#include "IRequest.hpp"
#include "ISafety.hpp"

#include <atomic>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

class Elevator
{
public:
    Elevator(const int elevatorId,
             const int minFloor,
             const int maxFloor);

    virtual ~Elevator();

    int                                      estimateArrival(const int targetFloor) const;

    int                                      getCurrentFloor()                      const;

    Direction                                getDirection()                         const;

    int                                      getId()                                const;

    std::optional<std::pair<int, Direction>> getRequestQueueFront()                 const;

    ElevatorState                            getState()                             const;

    void addObserver(IObserver* observer);

    void addRequest(std::unique_ptr<IRequest> request);

    void start();

    void stop();

    void enterEmergency();

    void resumeService();

    bool obstructDoor();

    bool clearObstruction();

protected:
    virtual int  moveToFloor(const int targetFloor) = 0;

    virtual void serveRequest()                     = 0;

    virtual void emergencyDescend()                 = 0;

    void notifyFloorArrival(const int floor);

    void notifyRequestServiced(const int floor);

    void notifyStateChanged(const ElevatorState newState);

    void runLoop();

    void setCurrentFloor(const int floor);

    void setDirection(const Direction direction);

    void setState(const ElevatorState state);

    void sortQueue();

    int                                   elevatorId;
    int                                   maximumFloor;
    int                                   minimumFloor;
    std::atomic<int>                      currentFloor;
    std::atomic<bool>                     running   = false;
    std::atomic<Direction>                direction = Direction::None;
    std::atomic<ElevatorState>            state     = ElevatorState::Idle;
    mutable std::mutex                    observerMutex;
    mutable std::mutex                    queueMutex;
    std::condition_variable               conditionVariable;
    std::deque<std::unique_ptr<IRequest>> requestQueue;
    std::unique_ptr<Door>                 door;
    std::unique_ptr<ISafety>              safety;
    std::vector<IObserver*>               observers;

private:
    std::thread workerThread;
};
