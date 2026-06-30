#pragma once

#include "AbstractRequest.hpp"
#include "Constant.hpp"

#include <atomic>
#include <chrono>

class ExternalRequest : public AbstractRequest
{
public:
    using Duration = std::chrono::steady_clock::duration;

    ExternalRequest(const int       floor,
                    const Direction direction,
                    const int       requestId,
                    const Duration  timeToLive = Constant::requestTimeToLive);

    bool isExpired()    const override;

private:
    std::chrono::steady_clock::duration timeToLive;
};
