#pragma once

#include <vector>

#include "Host.hpp"
#include "IPAddress.hpp"

struct HostListEntry;

enum class MessageType { JOINREQ, JOINREP, GOSSIP };

struct Message {
    IPAddress from;
    IPAddress to;
    MessageType msgType;
    unsigned long heartbeat;
    std::vector<HostListEntry> hostsList;
};