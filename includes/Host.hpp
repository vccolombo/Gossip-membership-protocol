#pragma once

#include "IPAddress.hpp"
#include "Message.hpp"
#include "Network.hpp"

class Network;

struct HostListEntry {
    IPAddress addr;
    unsigned int heartbeat;
    unsigned int timestam;
};

class Host {
   public:
    Host(std::string ip, Network* network);
    void receiveMessage(Message msg);
};