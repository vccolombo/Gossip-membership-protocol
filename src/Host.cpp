#include "Host.hpp"
// std::max
#include <cstdio>
#include <iostream>

#include "Config.hpp"
#include "Message.hpp"
#include "RandomUtil.hpp"

Host::Host(Address addr, Network* network) {
    this->addr = addr;
    this->network = network;

    this->network->connect(this->addr, this);

    // Add yourself to the list
    updateViewEntry(this->addr, 1);
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

    updateView(msg.payload.view);
}

void Host::receiveGOSSIP(Message msg) {
    printf("[%s] GOSSIP received from %s\n", this->addr.c_str(),
           msg.from.c_str());

    updateView(msg.payload.view);
}

void Host::updateView(const std::unordered_map<Address, unsigned long>& view) {
    for (auto const& row : view) {
        Address addr = row.first;
        unsigned int receivedHeartbeat = row.second;

        // If it is this host entry, ignore.
        // The host always knows better about itself
        if (addr == this->addr) continue;

        // Find and update/insert the entry
        updateViewEntry(addr, receivedHeartbeat);
    }
}

void Host::updateViewEntry(Address addr, unsigned long heartbeat) {
    // Create if not existent
    // Update if received heartbeat is more recent
    if (this->view[addr] < heartbeat) {
        this->view[addr] = heartbeat;
        this->lastUpdated[addr] = this->heartbeat;
        this->failures[addr] = false;
    }
}

void Host::processLoop() {
    // Update own view entry
    this->heartbeat++;
    updateViewEntry(this->addr, this->heartbeat);

    detectFailures();

    if (this->failed) return;

    sendGossip();
}

void Host::detectFailures() {
    auto it = this->lastUpdated.begin();
    while (it != this->lastUpdated.end()) {
        unsigned long diff = this->heartbeat - it->second;
        if (diff > Config::T_FAIL) {
            this->failures[it->first] = true;
        }

        if (diff > Config::T_DELETE) {
            this->view.erase(it->first);
            this->failures.erase(it->first);
            it = this->lastUpdated.erase(it);

            printf("[%s] Deleted %s from view\n", this->addr.c_str(),
                   it->first.c_str());
        } else {
            ++it;
        }
    }
}

void Host::sendGossip() {
    int gossipTo = RandomUtil::randomInt(0, this->view.size() - 1);
    for (auto& it : this->view) {
        if (gossipTo-- == 0) {
            return sendMessage(it.first, MessageType::GOSSIP);
        }
    }
}

void Host::sendMessage(Address to, MessageType msgType) {
    Message msg;
    msg.from = this->addr;
    msg.to = to;
    msg.msgType = msgType;
    msg.payload.view = getViewToSend();

    this->network->routeMessage(msg);
}

std::unordered_map<Address, unsigned long> Host::getViewToSend() {
    std::unordered_map<Address, unsigned long> viewToSend;

    for (auto& entry : this->failures) {
        Address addr = entry.first;
        bool failed = entry.second;
        if (!failed) {
            viewToSend[addr] = this->view[addr];
        }
    }

    return viewToSend;
}