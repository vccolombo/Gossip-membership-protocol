#include "Network.hpp"

#include "Host.hpp"
#include "IPAddress.hpp"
#include "Message.hpp"

void Network::connect(IPAddress ip, Host* host) {
    this->connectedHosts.insert({ip.getIP(), host});
}

void Network::routeMessage(Message msg) { this->messages.push(msg); }

void Network::dispatchMessages() {
    while (!this->messages.empty()) {
        Message msg = this->messages.front();

        this->connectedHosts[msg.to.getIP()]->receiveMessage(msg);

        this->messages.pop();
    }
}