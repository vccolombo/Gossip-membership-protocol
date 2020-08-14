#include "Network.hpp"

#include <iostream>

#include "Address.hpp"
#include "Config.hpp"
#include "Host.hpp"
#include "Message.hpp"
#include "RandomUtil.hpp"

void Network::connect(Address addr, Host* host) {
    this->connectedHosts.insert({addr, host});
}

void Network::routeMessage(Message msg) { this->messages.push(msg); }

void Network::dispatchMessages() {
    while (!this->messages.empty()) {
        Message msg = this->messages.front();

        if (RandomUtil::randomFloat(0.0, 1.0) > Config::MSG_DROP_CHANCE) {
            this->connectedHosts[msg.to]->receiveMessage(msg);
        } else {
            std::cout << "MSG dropped\n";
        }

        this->messages.pop();
    }
}