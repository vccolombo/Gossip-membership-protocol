#pragma once

#include <map>
#include <queue>
#include <random>

#include "../Configs.cpp"
#include "Host.hpp"
#include "IPAddress.hpp"
#include "Message.hpp"

class Network {
    std::map<IPAddress, Host*> hosts;
    std::queue<Message> messages;

   public:
    void connect(IPAddress ip, Host* member);
    void routeMessage(Message msg);
    void dispatchMessages();
};