#pragma once

#include <vector>

#include "IPAddress.hpp"

enum class MessageType { JOINREQ, JOINREP, GOSSIP };
struct Message {
    IPAddress from;
    IPAddress to;
    MessageType msgType;
    std::vector<HostsListEntry> membersList;
};