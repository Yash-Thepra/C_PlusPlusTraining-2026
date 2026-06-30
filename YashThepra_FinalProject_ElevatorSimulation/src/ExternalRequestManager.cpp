#include "ExternalRequestManager.hpp"
#include "ExternalRequest.hpp"

#include <vector>

ExternalRequestManager::ExternalRequestManager() = default;

bool ExternalRequestManager::RequestCompare::operator()(
    const std::unique_ptr<IRequest>& requestA,
    const std::unique_ptr<IRequest>& requestB) const
{
    return requestA->getPriority() < requestB->getPriority();
}

int ExternalRequestManager::PairHash::operator()(
    const std::pair<int, Direction>& pair) const
{
    const int hashFirst = std::hash<int>{}(pair.first);
    const int hashSecond = std::hash<std::uint8_t>{}(static_cast<std::uint8_t>(pair.second));
    return hashFirst ^ (hashSecond << 16U);
}


bool ExternalRequestManager::isButtonPressed(const int floor, const Direction direction)
{
    const auto key = std::make_pair(floor, direction);
    const auto it  = sharedButtons.find(key);
    return (it != sharedButtons.end() && it->second);
}

void ExternalRequestManager::onRequestServiced(const int floor, const Direction direction)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    const auto key           = std::make_pair(floor, direction);
    sharedButtons[key]     = false;
    conditionVariable.notify_one();
}

bool ExternalRequestManager::submitRequest(const IRequest& request)
{
    std::lock_guard<std::mutex> lock{mutexUtility};
    const auto key = std::make_pair(request.getFloor(), request.getDirection());
    bool result    = true;
    if (isButtonPressed(request.getFloor(), request.getDirection()))
    {
        result = false;
    }
    else
    {
        auto clone = std::make_unique<ExternalRequest>(
        request.getFloor(),
        request.getDirection(),
        request.getId());
        
        sharedButtons[key] = true;
        pendingQueue.push(std::move(clone));
        conditionVariable.notify_one();
    }
    return result;
}
