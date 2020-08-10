#pragma once

#include <bitset>
#include <string>

class IPAddress {
    std::bitset<8> ip[4];

    void setIPFromString(std::string ip);

   public:
    IPAddress(std::string ip);

    std::string getIP();
};