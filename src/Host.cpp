#include "Host.hpp"

#include "Config.hpp"
#include "Message.hpp"

Host::Host(Address addr, Network* network) {
    this->addr = addr;
    this->network = network;

    this->network->connect(this->addr, this);

    HostListEntry hle;
    hle.addr = this->addr;
    hle.heartbeat = this->heartbeat;
    hle.timestamp = this->localClock;
    this->hostsList.push_back(hle);
}

Host::Host(Address addr, Network* network, Address introducerAddr)
    : Host(addr, network) {
    sendMessage(introducerAddr, MessageType::JOINREQ);
}

void Host::receiveMessage(Message msg) {
    if (msg.msgType == MessageType::JOINREQ) {
        // JOINREQ
    } else if (msg.msgType == MessageType::JOINREP) {
        this->joined = true;
    } else if (msg.msgType == MessageType::GOSSIP) {
        // GOSSIP
    }
}

void Host::processLoop() {
    this->heartbeat++;

    if (!this->joined || this->failed) return;
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