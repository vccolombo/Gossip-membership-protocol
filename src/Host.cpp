#include "Host.hpp"

#include <cstdio>
#include <iostream>
#include <vector>

#include "Config.hpp"
#include "Message.hpp"

Host::Host(Address addr, Network* network) {
    this->addr = addr;
    this->network = network;

    this->network->connect(this->addr, this);

    insertEntry(this->addr, this->heartbeat);
}

Host::Host(Address addr, Network* network, Address introducerAddr)
    : Host(addr, network) {
    sendMessage(introducerAddr, MessageType::JOINREQ);
}

void Host::receiveMessage(Message msg) {
    updateLocalList(msg.from, msg.heartbeat);

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

    updateLocalList(msg.hostsList);

    sendMessage(msg.from, MessageType::JOINREP);
}

void Host::receiveJOINREP(Message msg) {
    printf("[%s] JOINREP received from %s\n", this->addr.c_str(),
           msg.from.c_str());

    this->joined = true;
}

void Host::receiveGOSSIP(Message msg) {}

void Host::updateLocalList(std::vector<HostListEntry> hostsList) {
    for (auto& hostEntry : hostsList) {
        updateLocalList(hostEntry);
    }
}

void Host::updateLocalList(Address addr, unsigned long heartbeat) {
    HostListEntry entry;
    entry.addr = addr;
    entry.heartbeat = heartbeat;
    entry.timestamp = this->localClock;

    updateLocalList(entry);
}

void Host::updateLocalList(HostListEntry hostEntry) {
    HostListEntry* localEntry = findEntry(hostEntry.addr);

    if (localEntry == nullptr) {
        return insertEntry(hostEntry);
    }

    if (hostEntry.heartbeat > localEntry->heartbeat) {
        localEntry->heartbeat = hostEntry.heartbeat;
        localEntry->timestamp = this->localClock;
    }
}

HostListEntry* Host::findEntry(Address addr) {
    for (auto& localEntry : this->hostsList) {
        if (localEntry.addr == addr) {
            return &localEntry;
        }
    }

    return nullptr;
}

void Host::insertEntry(HostListEntry entry) {
    insertEntry(entry.addr, entry.heartbeat);
}

void Host::insertEntry(Address addr, unsigned long heartbeat) {
    HostListEntry hle;
    hle.addr = addr;
    hle.heartbeat = heartbeat;
    hle.timestamp = this->localClock;

    this->hostsList.push_back(hle);
}

void Host::processLoop() {
    this->heartbeat++;

    if (!this->joined || this->failed) return;

    this->localClock++;
}

void Host::sendMessage(Address to, MessageType msgType) {
    Message msg;
    msg.from = this->addr;
    msg.to = to;
    msg.msgType = msgType;
    msg.heartbeat = this->heartbeat;
    msg.hostsList = this->hostsList;

    this->network->routeMessage(msg);
}