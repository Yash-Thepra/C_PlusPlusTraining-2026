#include "StandardElevator.hpp"

#include <thread>

StandardElevator::StandardElevator(const int      elevatorId,
                                   const int      minimumFloor,
                                   const int      maximumFloor,
                                   const Duration floorTravelTime)
    : Elevator{elevatorId, minimumFloor, maximumFloor}
    , floorTravelTime{floorTravelTime}
{
}

int StandardElevator::moveToFloor(const int targetFloor)
{
    const int current = getCurrentFloor();
    int       floorToMove;
    if (current == targetFloor)
    {
        floorToMove =  current;
    }
    else
    {
        Direction travelDirection = (targetFloor > current) ? Direction::Up : Direction::Down;
        setDirection(travelDirection);
        setState(travelDirection == Direction::Up ? ElevatorState::MovingUp
                                              : ElevatorState::MovingDown);
        int floor = current;
        while (floor != targetFloor && running.load(std::memory_order_acquire))
        {
            if (!safety->isOperational())
            {
                setState(ElevatorState::EmergencyStop);
                floorToMove = floor;
                break;
            }
            std::this_thread::sleep_for(floorTravelTime);
            floor += (travelDirection == Direction::Up) ? 1 : -1;
            setCurrentFloor(floor);
            notifyFloorArrival(floor);
            bool isBreaked = false;
            {
                std::lock_guard<std::mutex> lock{queueMutex};
                for (const auto& pending : requestQueue)
                {
                    if (pending->getFloor() == floor)
                    {
                        floorToMove = floor;
                        isBreaked = true;
                        break; 
                    }
                }   
            }
            if (isBreaked)
            {
                break;
            }
        }
    }
    return floorToMove;
}

void StandardElevator::serveRequest()
{
    std::unique_ptr<IRequest> request;
    {
        std::lock_guard<std::mutex> lock{queueMutex};
        if (requestQueue.empty())
        {
            return;
        }
        request = std::move(requestQueue.front());
        requestQueue.pop_front();
    }
    if (!request || request->isExpired())
    {
        setState(ElevatorState::Idle);
        return;
    }
    if (!safety->isOperational())
    {
        setState(ElevatorState::EmergencyStop);
        return;
    }
    const int originalTarget = request->getFloor();
    const int arrivedFloor   = moveToFloor(originalTarget);
    if (!running.load(std::memory_order_acquire))
    {
        return;
    }
    if (arrivedFloor != originalTarget)
    {
        std::lock_guard<std::mutex> lock{queueMutex};
        requestQueue.push_front(std::move(request));
        sortQueue();
        for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it)
        {
            if ((*it)->getFloor() == arrivedFloor)
            {
                requestQueue.erase(it);
                break;
            }
        }
    }
    const int targetFloor = arrivedFloor;
    if (!running.load(std::memory_order_acquire))
    {
        return;
    }
    setState(ElevatorState::DoorOpen);
    door->open();
    const auto normalDeadline = std::chrono::steady_clock::now() +
                                Constant::doorOpenDuration +
                                std::chrono::milliseconds{500};

    while (door->getState() != DoorState::Closed &&
           std::chrono::steady_clock::now() < normalDeadline &&
           running.load(std::memory_order_acquire))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
    while (door->isObstructed() && running.load(std::memory_order_acquire))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{200});
    }
    if (!running.load(std::memory_order_acquire))
    {
        return;
    }
    door->close();
    setState(ElevatorState::DoorClosed);

    notifyRequestServiced(targetFloor);
    {
        std::lock_guard<std::mutex> lock{queueMutex};
        if (requestQueue.empty())
        {
            setState(ElevatorState::Idle);
            setDirection(Direction::None);
        }
    }
}

void StandardElevator::emergencyDescend()
{
    const int target = Constant::defaultFloorInEmergency;
    int       floor  = getCurrentFloor();
    if (floor == target)
    {
        setState(ElevatorState::DoorOpen);
        door->open();
        return;
    }
    const Direction currentDirection = (target > floor) ? Direction::Up : Direction::Down;
    setDirection(currentDirection);
    setState(currentDirection == Direction::Up ? ElevatorState::MovingUp : ElevatorState::MovingDown);
    while (floor != target && running.load(std::memory_order_acquire))
    {
        std::this_thread::sleep_for(floorTravelTime);
        floor += (currentDirection == Direction::Up) ? 1 : -1;
        setCurrentFloor(floor);
        notifyFloorArrival(floor);
    }
    setDirection(Direction::None);
    setState(ElevatorState::DoorOpen);
    door->open();
}
