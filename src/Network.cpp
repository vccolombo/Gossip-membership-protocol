#include "Network.hpp"

#include "Host.hpp"
#include "Address.hpp"
#include "Message.hpp"

void Network::connect(Address addr, Host* host) {
    this->connectedHosts.insert({addr, host});
}

void Network::routeMessage(Message msg) { this->messages.push(msg); }

void Network::dispatchMessages() {
    while (!this->messages.empty()) {
        Message msg = this->messages.front();

        this->connectedHosts[msg.to]->receiveMessage(msg);

        this->messages.pop();
    }
}