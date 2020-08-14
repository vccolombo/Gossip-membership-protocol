#include "Network.hpp"

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
        this->messages.pop();

        if (msg.msgType == MessageType::GOSSIP &&
            RandomUtil::randomFloat(0., 1.) < Config::MSG_DROP_CHANCE) {
            continue;
        } else {
            // Always forward JOIN messages
            this->connectedHosts[msg.to]->receiveMessage(msg);
        }
    }
}