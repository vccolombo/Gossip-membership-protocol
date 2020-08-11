#include "Host.hpp"

#include "Config.hpp"
#include "Message.hpp"

Host::Host(Address addr, Network* network) {
    this->addr = addr;
    this->network = network;

    this->network->connect(this->addr, this);
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

void Host::processLoop() { this->heartbeat++; }

void Host::sendMessage() {}