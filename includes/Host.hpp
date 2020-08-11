#pragma once

#include <vector>

#include "Address.hpp"
#include "Message.hpp"
#include "Network.hpp"

class Network;

struct HostListEntry {
    Address addr;
    unsigned long heartbeat;
    unsigned long timestam;
};

class Host {
    Network* network;
    unsigned long localClock;
    bool joined = false;
    unsigned long heartbeat;
    std::vector<HostListEntry> hostsList;

    void sendMessage();

   public:
    Address addr;

    Host(Address addr, Network* network);
    void receiveMessage(Message msg);
    void processLoop();
};