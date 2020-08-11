#pragma once

#include <string>

class IPAddress {
    uint8_t ip[4] = {0};

    void setIPFromString(std::string ip);

   public:
    IPAddress(std::string ip);

    bool operator==(IPAddress &rhs);

    std::string getIP();
};