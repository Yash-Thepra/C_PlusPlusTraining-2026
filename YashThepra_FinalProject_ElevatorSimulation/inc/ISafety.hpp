#pragma once

class ISafety
{
public:
    virtual ~ISafety() = default;

    virtual bool isOperational()            const = 0;

    virtual void onPowerFailure()                 = 0;

    virtual void resetSafety()                    = 0;

    virtual void triggerEmergency()               = 0;
};
