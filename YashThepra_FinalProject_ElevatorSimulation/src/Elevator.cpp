#include "Elevator.hpp"
#include "SafetyController.hpp"

#include <algorithm>
#include <stdexcept>

Elevator::Elevator(const int elevatorId, const int minFloor, const int maxFloor)
    : elevatorId{elevatorId}
    , minimumFloor{minFloor}
    , maximumFloor{maxFloor}
    , currentFloor{Constant::groundFloor}
    , door{std::make_unique<Door>()}
    , safety{std::make_unique<SafetyController>()}
{
    if (minFloor >= maxFloor)
    {
        throw std::invalid_argument{"Elevator: minFloor must be less than maxFloor"};
    }
}

Elevator::~Elevator()
{
    stop();
}

void Elevator::addObserver(IObserver* observer)
{
    if (observer == nullptr)
    {
        return;
    }
    std::lock_guard<std::mutex> lock{observerMutex};
    observers.push_back(observer);
}

void Elevator::addRequest(std::unique_ptr<IRequest> request)
{
    if (!request || !safety->isOperational() || door->isObstructed())
    {
        return;
    }
    {
        std::lock_guard<std::mutex> lock{queueMutex};
        requestQueue.push_back(std::move(request));
        sortQueue();
    }
    conditionVariable.notify_one();
}

int Elevator::estimateArrival(const int targetFloor) const
{
    return std::abs(currentFloor.load(std::memory_order_acquire) - targetFloor);
}

int Elevator::getCurrentFloor() const
{
    return currentFloor.load(std::memory_order_acquire);
}

Direction Elevator::getDirection() const
{
    return direction.load(std::memory_order_acquire);
}

int Elevator::getId() const
{
    return elevatorId;
}

std::optional<std::pair<int, Direction>> Elevator::getRequestQueueFront() const
{
    std::lock_guard<std::mutex> lock{queueMutex};
    if (requestQueue.empty())
    {
        return std::nullopt;
    }
    return std::make_pair(requestQueue.front()->getFloor(),
                          requestQueue.front()->getDirection());
}

ElevatorState Elevator::getState() const
{
    return state.load(std::memory_order_acquire);
}

void Elevator::notifyFloorArrival(const int floor)
{
    std::lock_guard<std::mutex> lock{observerMutex};
    for (auto* observer : observers)
    {
        if (observer != nullptr)
        {
            observer->onFloorArrival(elevatorId, floor);
        }
    }
}

void Elevator::notifyRequestServiced(const int floor)
{
    std::lock_guard<std::mutex> lock{observerMutex};
    for (auto* observer : observers)
    {
        if (observer != nullptr)
        {
            observer->onRequestServiced(elevatorId, floor);
        }
    }
}

void Elevator::notifyStateChanged(const ElevatorState newState)
{
    std::lock_guard<std::mutex> lock{observerMutex};
    for (auto* observer : observers)
    {
        if (observer != nullptr)
        {
            observer->onStateChanged(elevatorId, newState);
        }
    }
}

void Elevator::runLoop()
{
    while (running.load(std::memory_order_acquire))
    {
        std::unique_lock<std::mutex> lock{queueMutex};
        conditionVariable.wait(lock, [this] {
            const bool stopping  = !running.load(std::memory_order_acquire);
            const bool emergency = state.load(std::memory_order_acquire) ==
                                    ElevatorState::EmergencyStop;
            return stopping || (!emergency && !requestQueue.empty());
        });
        if (!running.load(std::memory_order_acquire))
        {
            break;
        }
        if (state.load(std::memory_order_acquire) == ElevatorState::EmergencyStop)
        {
            continue;
        }
        if (requestQueue.empty())
        {
            continue;
        }
        lock.unlock();
        serveRequest();
    }
    setState(ElevatorState::Idle);
}

void Elevator::setCurrentFloor(const int floor)
{
    currentFloor.store(floor, std::memory_order_release);
}

void Elevator::setDirection(const Direction elevatorDirection)
{
    direction.store(elevatorDirection, std::memory_order_release);
}

void Elevator::setState(const ElevatorState elevatorState)
{
    state.store(elevatorState, std::memory_order_release);
    notifyStateChanged(elevatorState);
}

void Elevator::sortQueue()
{
    const int       current    = currentFloor.load(std::memory_order_acquire);
    const Direction directions = direction.load(std::memory_order_acquire);
    std::stable_sort(requestQueue.begin(), requestQueue.end(),
        [current, directions](const std::unique_ptr<IRequest>& firstRequest,
                   const std::unique_ptr<IRequest>& secondRequest)
        {
            if (firstRequest->getPriority() != secondRequest->getPriority())
            {
                return firstRequest->getPriority() > secondRequest->getPriority();
            }
            const int floorA = firstRequest->getFloor();
            const int floorB = secondRequest->getFloor();
            if (directions == Direction::Up)
            {
                const bool aheadA = (floorA >= current);
                const bool aheadB = (floorB >= current);
                if (aheadA != aheadB)
                {
                    return aheadA;
                }
                return floorA < floorB;
            }
            if (directions == Direction::Down)
            {
                const bool aheadA = (floorA <= current);
                const bool aheadB = (floorB <= current);
                if (aheadA != aheadB)
                {
                    return aheadA;
                }
                return floorA > floorB; 
            }
            const int distanceA = std::abs(floorA - current);
            const int distanceB = std::abs(floorB - current);
            return distanceA < distanceB;
        });
}

void Elevator::start()
{
    if (running.exchange(true, std::memory_order_acq_rel))
    {
        return;
    }
    setState(ElevatorState::Idle);
    workerThread = std::thread{&Elevator::runLoop, this};
}

void Elevator::stop()
{
    running.store(false, std::memory_order_release);
    conditionVariable.notify_all();
    if (workerThread.joinable())
    {
        workerThread.join();
    }
}

void Elevator::enterEmergency()
{
    {
        std::lock_guard<std::mutex> lock{queueMutex};
        requestQueue.clear();         
    }
    safety->triggerEmergency();       
    setDirection(Direction::None);
    setState(ElevatorState::EmergencyStop);
    conditionVariable.notify_all();                 
    emergencyDescend();                
}

void Elevator::resumeService()
{
    safety->resetSafety();            
    setState(ElevatorState::Idle);
    setDirection(Direction::None);
    conditionVariable.notify_all();
}

bool Elevator::obstructDoor()
{
    bool obstructFlag = true;
    if (state.load(std::memory_order_acquire) != ElevatorState::DoorOpen)
    {
        obstructFlag = false;
    }
    else
    {
        door->setObstructed(true);
    }
    return obstructFlag;
}

bool Elevator::clearObstruction()
{
    bool isCleared = true;
    if (!door->isObstructed())
    {
        isCleared = false;
    }
    else 
    {
        door->setObstructed(false);
    }
    conditionVariable.notify_all();
    return isCleared;
}
