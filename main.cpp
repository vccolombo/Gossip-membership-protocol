#include <iostream>

#include "src/IPAddress.hpp"

int main() {
    IPAddress ip("255.255.255.255");

    std::cout << ip.getIP() << std::endl;
}