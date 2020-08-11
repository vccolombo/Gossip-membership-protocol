#pragma once

#include "IPAddress.hpp"
#include "Message.hpp"
#include "Network.hpp"

class Network;

struct HostListEntry {
    IPAddress ip;
    unsigned long heartbeat;
    unsigned long timestam;
};

class Host {
    IPAddress ip;
    Network* network;
    unsigned long heartbeat;

   public:
    Host(std::string ip, Network* network);
    void receiveMessage(Message msg);
};