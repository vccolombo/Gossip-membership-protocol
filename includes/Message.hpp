#pragma once

#include <vector>

#include "Host.hpp"
#include "Address.hpp"

struct HostListEntry;

enum class MessageType { JOINREQ, JOINREP, GOSSIP };

struct Message {
    Address from;
    Address to;
    MessageType msgType;
    unsigned long heartbeat;
    std::vector<HostListEntry> hostsList;
};