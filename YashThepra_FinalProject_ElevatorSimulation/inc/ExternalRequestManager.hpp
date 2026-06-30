#pragma once

#include "IRequest.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class ExternalRequestManager
{
public:
    ExternalRequestManager();

    bool        submitRequest(const IRequest& request); 

    void        onRequestServiced(const int floor, const Direction direction);

private:
    struct RequestCompare
    {
        bool operator()(const std::unique_ptr<IRequest>& requestA,
                        const std::unique_ptr<IRequest>& requestB) const;
    };

    struct PairHash
    {
        int operator()(const std::pair<int, Direction>& pair) const;
    };

    using PriorityQueue = std::priority_queue<std::unique_ptr<IRequest>,
                                              std::vector<std::unique_ptr<IRequest>>, 
                                              RequestCompare>;

    using ButtonMap     = std::unordered_map<std::pair<int, Direction>, bool, PairHash>;

    bool isButtonPressed(const int floor, const Direction direction);

    std::condition_variable conditionVariable;
    PriorityQueue           pendingQueue;
    ButtonMap               sharedButtons;
    mutable std::mutex      mutexUtility;
};
