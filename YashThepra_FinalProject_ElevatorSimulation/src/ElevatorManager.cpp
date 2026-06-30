#include "ElevatorManager.hpp"
#include "RequestFactory.hpp"

#include <algorithm>
#include <stdexcept>

ElevatorManager::ElevatorManager(IScheduler* scheduler)
    : scheduler{scheduler}
    , externalRequestManager{std::make_unique<ExternalRequestManager>()}
{
    if (scheduler == nullptr)
    {
        throw std::invalid_argument{"ElevatorManager: scheduler must not be null"};
    }
}

void ElevatorManager::addElevator(std::unique_ptr<Elevator> elevator)
{
    if (!elevator)
    {
        return;
    }
    std::lock_guard<std::mutex> lock{mutexUtility};
    elevator->addObserver(this);
    scheduler->registerElevator(elevator.get());
    elevators.push_back(std::move(elevator));
}

void ElevatorManager::addObserverToAll(IObserver* observer)
{
    if (observer == nullptr)
    {
        return;
    }
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& elevator : elevators)
    {
        if (elevator)
        {
            elevator->addObserver(observer);
        }
    }
}

int ElevatorManager::getElevatorCount() const
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    return elevators.size();
}

Elevator* ElevatorManager::getElevatorById(const int id) const
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (const auto& elevator : elevators)
    {
        if (elevator && elevator->getId() == id)
        {
            return elevator.get();
        }
    }
    return nullptr;
}

void ElevatorManager::handleExternalRequest(const int floor, const Direction direction)
{
    auto request        = RequestFactory::createExternal(floor, direction);
    const bool accepted = externalRequestManager->submitRequest(*request);
    if (!accepted)
    {
        return;
    }
    scheduler->schedule(*request);
}

void ElevatorManager::handleInternalRequest(const int elevatorId, const int destinationFloor)
{
    auto* elevator = getElevatorById(elevatorId);
    if (elevator == nullptr)
    {
        return;
    }
    auto request = RequestFactory::createInternal(elevatorId, destinationFloor);
    elevator->addRequest(std::move(request));
}

void ElevatorManager::startAll()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& elevator : elevators)
    {
        if (elevator)
        {
            elevator->start();
        }
    }
}

void ElevatorManager::stopAll()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& elevator : elevators)
    {
        if (elevator)
        {
            elevator->stop();
        }
    }
}

void ElevatorManager::triggerEmergencyAll()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& elevator : elevators)
    {
        if (elevator)
        {
            elevator->enterEmergency();
        }
    }
}

void ElevatorManager::triggerEmergency(int elevatorId)
{
    auto* elevator = getElevatorById(elevatorId);
    if (elevator != nullptr)
    {
        elevator->enterEmergency();
    }
}

void ElevatorManager::resumeServiceAll()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    for (auto& elevator : elevators)
    {
        if (elevator)
        {
            elevator->resumeService();
        }
    }
}

void ElevatorManager::resumeService(const int elevatorId)
{
    auto* elevator = getElevatorById(elevatorId);
    if (elevator != nullptr)
    {
        elevator->resumeService();
    }
}

bool ElevatorManager::obstructDoor(const int elevatorId)
{
    auto* elevator    = getElevatorById(elevatorId);
    return (elevator != nullptr) && elevator->obstructDoor();
}

bool ElevatorManager::clearObstruction(const int elevatorId)
{
    auto* elevator    = getElevatorById(elevatorId);
    return (elevator != nullptr) && elevator->clearObstruction();
}

void ElevatorManager::onFloorArrival(int, int)
{
    //empty implementation to prevent the class from becoming abstract — 
    //DisplayPanel/Logger consume it directly.
}

void ElevatorManager::onRequestServiced(const int elevatorId, const int floor)
{
    externalRequestManager->onRequestServiced(floor, Direction::Up);
    externalRequestManager->onRequestServiced(floor, Direction::Down);
}

void ElevatorManager::onStateChanged(int, const ElevatorState)
{
    //just for implementation purpose to prevent the class from becoming abstract.
}
