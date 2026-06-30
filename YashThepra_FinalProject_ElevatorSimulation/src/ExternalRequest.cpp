#include "ExternalRequest.hpp"
#include "Constant.hpp"

ExternalRequest::ExternalRequest(const int       floor,
                                 const Direction direction,
                                 const int       id,
                                 const Duration  timeToLive)
    : AbstractRequest{RequestConfiguration{floor,
                                           direction,
                                           (direction == Direction::Up ? RequestType::ExternalUp
                                                                       : RequestType::ExternalDown),
                                           Constant::normalRequestPriority,
                                           id}}
                                           , timeToLive{timeToLive}
{
}

bool ExternalRequest::isExpired() const
{
    const auto age = std::chrono::steady_clock::now() - timestamp;
    return age > timeToLive;
}
