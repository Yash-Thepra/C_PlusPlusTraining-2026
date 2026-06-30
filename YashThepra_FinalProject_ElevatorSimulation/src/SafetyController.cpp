#include "SafetyController.hpp"

#include <stdexcept>

SafetyController::SafetyController(const float maximumWeightKg)
    : maximumWeightKg{maximumWeightKg}
{
    if (maximumWeightKg <= 0.0F)
    {
        throw std::invalid_argument{"SafetyController: maxWeightKg must be positive"};
    }
}

bool SafetyController::isOperational() const
{
    return operational.load(std::memory_order_acquire);
}

void SafetyController::onPowerFailure()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    operational.store(false, std::memory_order_release);
}

void SafetyController::resetSafety()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    operational.store(true, std::memory_order_release);
}

void SafetyController::triggerEmergency()
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    operational.store(false, std::memory_order_release);
}
