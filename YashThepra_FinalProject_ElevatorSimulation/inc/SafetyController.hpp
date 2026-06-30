#pragma once

#include "Constant.hpp"
#include "ISafety.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>

class SafetyController : public ISafety
{
public:
    SafetyController(const float maximumWeightInKg = Constant::maximumWeightInKg);

    bool  isOperational()                const override;
    void  onPowerFailure()               override;
    void  resetSafety()                  override;
    void  triggerEmergency()             override;

private:
    float                   maximumWeightKg;
    std::atomic<bool>       operational = true;
    mutable std::mutex      mutexUtility;
};
