#include <iostream>

#include "src/IPAddress.hpp"

int main() {
    IPAddress ip("255.255.255.254");

    std::cout << ip.getIP() << std::endl;
}