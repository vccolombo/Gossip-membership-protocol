#pragma once

#include <queue>
#include <unordered_map>

#include "Host.hpp"
#include "Address.hpp"
#include "Message.hpp"

class Host;

class Network {
    std::unordered_map<Address, Host*> connectedHosts;
    std::queue<Message> messages;

   public:
    void connect(Address addr, Host* host);
    void routeMessage(Message msg);
    void dispatchMessages();
};