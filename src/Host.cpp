#include "Host.hpp"

#include "Message.hpp"

Host::Host(std::string ip, Network* network) {
    this->ip = IPAddress(ip);
    this->network = network;
}

void Host::receiveMessage(Message msg) {
    if (msg.msgType == MessageType::JOINREQ) {
        // JOINREQ
    } else if (msg.msgType == MessageType::JOINREP) {
        // JOINREP
    } else if (msg.msgType == MessageType::GOSSIP) {
        // GOSSIP
    }
}