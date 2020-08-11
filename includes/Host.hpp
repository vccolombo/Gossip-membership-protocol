#pragma once

#include <vector>

#include "Address.hpp"
#include "Message.hpp"
#include "Network.hpp"

class Network;

struct HostListEntry {
    Address addr;
    unsigned long heartbeat;
    unsigned long timestamp;
};

class Host {
    Network* network;
    unsigned long localClock = 0;
    unsigned long heartbeat = 0;
    std::vector<HostListEntry> hostsList;
    bool joined = false;
    bool failed = false;

    void receiveJOINREQ(Message msg);
    void receiveJOINREP(Message msg);
    void receiveGOSSIP(Message msg);
    void updateLocalList(std::vector<HostListEntry> hostsList);
    void updateLocalList(Address addr, unsigned long heartbeat);
    void updateLocalList(HostListEntry hostsList);
    HostListEntry* findEntry(Address addr);
    void insertEntry(HostListEntry entry);
    void insertEntry(Address addr, unsigned long heartbeat);
    void sendMessage(Address to, MessageType msgType);

   public:
    Address addr;

    Host(Address addr, Network* network);
    Host(Address addr, Network* network, Address introducerAddr);
    void receiveMessage(Message msg);
    void processLoop();
};