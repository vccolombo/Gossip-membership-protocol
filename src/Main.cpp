#include <iostream>

#include "Config.hpp"
#include "Network.hpp"

int main() {
    Network* network = new Network();

    Host* host0 = new Host("192.168.0.10", network);
    Host* host1 = new Host("192.168.0.11", network, "192.168.0.10");
    Host* host2 = new Host("192.168.0.12", network, "192.168.0.10");
    Host* host3 = new Host("192.168.0.13", network, "192.168.0.10");
    Host* host4 = new Host("192.168.0.14", network, "192.168.0.10");
    Host* host5 = new Host("192.168.0.15", network, "192.168.0.10");
    Host* host6 = new Host("192.168.0.16", network, "192.168.0.10");
    Host* host7 = new Host("192.168.0.17", network, "192.168.0.10");
    Host* host8 = new Host("192.168.0.18", network, "192.168.0.10");
    Host* host9 = new Host("192.168.0.19", network, "192.168.0.10");

    for (size_t cycle = 1; cycle <= Config::NUMBER_OF_LOOPS; cycle++) {
        std::cout << "Cycle " << cycle << std::endl;

        network->dispatchMessages();

        host0->processLoop();
        host1->processLoop();
        host2->processLoop();
        host3->processLoop();
        host4->processLoop();
        host5->processLoop();
        host6->processLoop();
        host7->processLoop();
        host8->processLoop();
        host9->processLoop();

        if (cycle == 50) {
            host1->failed = true;
            host2->failed = true;
        }

        std::cout << std::endl;
    }

    delete host0;
    delete host1;
    delete host2;
    delete network;
}