#pragma once

#include <queue>
#include <unordered_map>

#include "Address.hpp"
#include "Host.hpp"
#include "Message.hpp"

class Host;

class Network {
    std::unordered_map<Address, Host*> connectedHosts;
    std::queue<Message> messages;
    unsigned long totalBandwidth = 0;

   public:
    ~Network();
    void connect(Address addr, Host* host);
    void routeMessage(Message msg);
    void dispatchMessages();
};