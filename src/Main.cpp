#include <iostream>

#include "Config.hpp"
#include "Network.hpp"

int main() {
    Network* network = new Network();

    Host* host1 = new Host("192.168.0.10", network);
    Host* host2 = new Host("192.168.0.11", network);
    Host* host3 = new Host("192.168.0.12", network);

    for (size_t i = 1; i <= Config::NUMBER_OF_LOOPS; i++) {
        std::cout << "Loop " << i << std::endl;

        network->dispatchMessages();
        host1->processLoop();
        host2->processLoop();
        host3->processLoop();

        std::cout << std::endl;
    }

    delete network;
}