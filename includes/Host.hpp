#pragma once

#include <unordered_map>

#include "Address.hpp"
#include "Message.hpp"
#include "Network.hpp"

class Network;

class Host {
    Network* network;
    std::unordered_map<Address, unsigned long> view;
    std::unordered_map<Address, unsigned long> lastUpdated;
    unsigned long heartbeat = 0;

    void receiveJOINREQ(Message msg);
    void receiveJOINREP(Message msg);
    void receiveGOSSIP(Message msg);
    void updateView(const std::unordered_map<Address, unsigned long>& view);
    void updateViewEntry(Address addr, unsigned long heartbeat);
    void sendGossip();
    void sendMessage(Address to, MessageType msgType);

   public:
    Address addr;
    bool failed = false;

    Host(Address addr, Network* network);
    Host(Address addr, Network* network, Address introducerAddr);
    void receiveMessage(Message msg);
    void processLoop();
};