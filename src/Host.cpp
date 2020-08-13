#include "Host.hpp"
// std::max
#include <cstdio>
#include <iostream>

#include "Config.hpp"
#include "Message.hpp"

Host::Host(Address addr, Network* network) {
    this->addr = addr;
    this->network = network;

    this->network->connect(this->addr, this);

    // Add yourself to the list
    updateViewEntry(this->addr, this->heartbeat);
}

Host::Host(Address addr, Network* network, Address introducerAddr)
    : Host(addr, network) {
    sendMessage(introducerAddr, MessageType::JOINREQ);
}

void Host::receiveMessage(Message msg) {
    if (msg.msgType == MessageType::JOINREQ) {
        receiveJOINREQ(msg);
    }
    if (msg.msgType == MessageType::JOINREP) {
        receiveJOINREP(msg);
    }
    if (msg.msgType == MessageType::GOSSIP) {
        receiveGOSSIP(msg);
    }
}

void Host::receiveJOINREQ(Message msg) {
    printf("[%s] JOINREQ received from %s\n", this->addr.c_str(),
           msg.from.c_str());

    updateView(msg.payload.view);

    sendMessage(msg.from, MessageType::JOINREP);
}

void Host::receiveJOINREP(Message msg) {
    printf("[%s] JOINREP received from %s\n", this->addr.c_str(),
           msg.from.c_str());

    this->joined = true;
}

void Host::receiveGOSSIP(Message msg) {}

void Host::updateView(const std::unordered_map<Address, unsigned long>& view) {
    for (auto const& row : view) {
        Address addr = row.first;
        unsigned int receivedHeartbeat = row.second;

        // If it is this host entry, ignore.
        // The host always knows better about itself
        if (addr == this->addr) continue;

        // Find and update/insert the entry
        updateViewEntry(addr, receivedHeartbeat);

        std::cout << addr << " " << this->view[addr] << " "
                  << this->lastUpdated[addr] << std::endl;
    }
}

void Host::updateViewEntry(Address addr, unsigned long heartbeat) {
    // Create if not existent
    // Update if received heartbeat is more recent
    if (this->view[addr] < heartbeat) {
        this->view[addr] = heartbeat;
        this->lastUpdated[addr] = this->heartbeat;
    }
}

void Host::processLoop() {
    // Update own view entry
    this->heartbeat++;
    updateViewEntry(this->addr, this->heartbeat);

    if (!this->joined || this->failed) return;

    // Send gossip
    // ...
}

void Host::sendMessage(Address to, MessageType msgType) {
    Message msg;
    msg.from = this->addr;
    msg.to = to;
    msg.msgType = msgType;
    msg.payload.view = this->view;

    this->network->routeMessage(msg);
}