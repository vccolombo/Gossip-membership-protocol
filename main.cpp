#include <iostream>

#include "src/IPAddress.hpp"

int main() {
    IPAddress ip("192.168.0.17");

    std::cout << ip.getIP() << std::endl;
}