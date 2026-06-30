#pragma once

#include "Elevator.hpp"
#include "ExternalRequestManager.hpp"
#include "IObserver.hpp"
#include "IScheduler.hpp"

#include <memory>
#include <mutex>

class ElevatorManager : public IObserver
{
public:
    ElevatorManager(IScheduler* scheduler);

    int       getElevatorCount()            const;

    Elevator* getElevatorById(const int id) const;

    void addElevator(std::unique_ptr<Elevator> elevator);

    void addObserverToAll(IObserver* observer);

    void handleExternalRequest(const int floor, const Direction direction);

    void handleInternalRequest(const int elevatorId, const int destinationFloor);

    void startAll();

    void stopAll();

    void triggerEmergencyAll();

    void triggerEmergency(const int elevatorId);

    void resumeServiceAll();

    void resumeService(const int elevatorId);

    bool obstructDoor(const int elevatorId);

    bool clearObstruction(const int elevatorId);

    void onFloorArrival(const int elevatorId, const int floor)     override;

    void onRequestServiced(const int elevatorId, const int floor)  override;

    void onStateChanged(int elevatorId, const ElevatorState state) override;

private:
    IScheduler*                             scheduler;
    std::vector<std::unique_ptr<Elevator>>  elevators;
    std::unique_ptr<ExternalRequestManager> externalRequestManager;
    mutable std::mutex                      mutexUtility;
};
