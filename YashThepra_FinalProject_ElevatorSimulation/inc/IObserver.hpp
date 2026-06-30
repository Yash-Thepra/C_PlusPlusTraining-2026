#pragma once

enum class ElevatorState
{
    Idle,
    MovingUp,
    MovingDown,
    DoorOpen,
    DoorClosed,
    Maintenance,
    OutOfService,
    EmergencyStop
};

class IObserver
{
public:
    virtual ~IObserver() {};

    virtual void onFloorArrival(const int elevatorId, const int floor)     = 0;

    virtual void onRequestServiced(const int elevatorId, const int floor)  = 0;

    virtual void onStateChanged(int elevatorId, const ElevatorState state) = 0;
};
