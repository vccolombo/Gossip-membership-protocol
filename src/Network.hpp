#pragma once

#include <map>

#include "IPAddress.hpp"
#include "Message.hpp"
#include "NodeMember.hpp"

class Network {
    std::map<IPAddress, NodeMember*> m;

   public:
    IPAddress connect(NodeMember*);
    void routeMessage(Message);
};