#include <iostream>

#include "Config.hpp"
#include "Network.hpp"

int main() {
    Network* network = new Network();

    Host* host0 = new Host("192.168.0.10", network);
    Host* host1 = new Host("192.168.0.11", network, "192.168.0.10");
    Host* host2 = new Host("192.168.0.12", network, "192.168.0.10");

    for (size_t cycle = 1; cycle <= Config::NUMBER_OF_LOOPS; cycle++) {
        std::cout << "Cycle " << cycle << std::endl;

        network->dispatchMessages();

        host0->processLoop();
        host1->processLoop();
        host2->processLoop();

        std::cout << std::endl;
    }

    delete network;
}