#include "InternalRequest.hpp"
#include "Constant.hpp"

InternalRequest::InternalRequest(const int requestId, 
                                 const int destinationFloor, 
                                 const int elevatorId)
    : AbstractRequest{RequestConfiguration{destinationFloor,
                      Direction::None,
                      RequestType::Internal,
                      Constant::normalRequestPriority,
                      requestId}}
{
}

bool InternalRequest::isExpired() const
{
    return false;
}
