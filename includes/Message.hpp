#pragma once

#include <unordered_map>

#include "Address.hpp"

enum class MessageType { JOINREQ, JOINREP, GOSSIP };

struct MessagePayload {
    std::unordered_map<Address, unsigned long> view;
};

struct Message {
    Address from;
    Address to;
    MessageType msgType;
    MessagePayload payload;
};