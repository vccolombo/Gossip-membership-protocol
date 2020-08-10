#include "Network.hpp"

#include "utils/random.cpp"

void Network::connect(IPAddress ip, Host* member) {
    this->hosts.insert({ip, member});
}

void Network::routeMessage(Message msg) { this->messages.push(msg); }

void Network::dispatchMessages() {
    while (!this->messages.empty()) {
        Message msg = this->messages.front();
        this->messages.pop();

        if (Random::randomFloat(0, 1) >= Configs::MSG_FAILURE_CHANCE) {
            hosts[msg.to]->receiveMessage(msg);
        }
    }
}