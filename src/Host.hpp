#pragma once

#include <string>
#include <vector>

#include "IPAddress.hpp"
#include "Message.hpp"
#include "Network.hpp"

struct HostsListEntry {
    IPAddress ip;
    int heartbeat;
    int timestamp;
};

class Host {
    IPAddress ip;
    Network* network;
    int heartbeat;
    std::vector<HostsListEntry> hostsList;
    bool failed = false;

    void sendMessage(Message msg);

   public:
    Host(std::string ip, Network* network);

    void receiveMessage(Message msg);
    void runLoop();
};