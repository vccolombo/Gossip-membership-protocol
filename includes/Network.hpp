#pragma once

#include <queue>
#include <unordered_map>

#include "Host.hpp"
#include "IPAddress.hpp"
#include "Message.hpp"

class Host;

class Network {
    std::unordered_map<std::string, Host*> connectedHosts;
    std::queue<Message> messages;

   public:
    Network(){};
    void connect(IPAddress ip, Host* host);
    void routeMessage(Message msg);
    void dispatchMessages();
};