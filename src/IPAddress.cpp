#include "IPAddress.hpp"

#include <stdlib.h>

#include <stdexcept>

IPAddress::IPAddress(std::string ip) { setIPFromString(ip); }

bool IPAddress::operator==(IPAddress &rhs) {
    return this->getIP() == rhs.getIP();
}

void IPAddress::setIPFromString(std::string ip) {
    std::string delimiter = ".";

    size_t pos = 0, part = 0;
    while (pos != std::string::npos) {
        pos = ip.find(delimiter);
        int sub = atoi(ip.substr(0, pos).c_str());

        if (part >= 4 || sub < 0 || sub > 255) {
            throw std::invalid_argument("Invalid IP");
        }

        this->ip[part++] = std::bitset<8>(sub);

        ip.erase(0, pos + delimiter.length());
    }
}

std::string IPAddress::getIP() {
    std::string result;
    for (size_t i = 0; i < 4; i++) {
        if (i != 0) {
            result += ".";
        }

        result += std::to_string(this->ip[i].to_ulong());
    }

    return result;
}