#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

#include "Config.hpp"
#include "Host.hpp"
#include "Network.hpp"
#include "RandomUtil.hpp"

int main() {
    Network* network = new Network();
    std::vector<Host*> hosts;

    printf("Running test file %s\n", Config::TEST_FILE.c_str());

    std::ifstream testFile;
    testFile.open(Config::TEST_FILE);

    std::string hostIp, introducerIp;
    if (testFile.is_open()) {
        // get introducers
        while (getline(testFile, hostIp) && hostIp != "") {
            Host* host = new Host(hostIp, network);
            hosts.push_back(host);
        }

        // get other hosts
        while (getline(testFile, hostIp, ' ') &&
               getline(testFile, introducerIp)) {
            Host* host = new Host(hostIp, network, introducerIp);
            hosts.push_back(host);
        }
        testFile.close();
    }

    for (size_t cycle = 1; cycle <= Config::NUMBER_OF_LOOPS; cycle++) {
        std::cout << "Cycle " << cycle << std::endl;

        network->dispatchMessages();

        for (auto& host : hosts) {
            if (cycle == Config::NUMBER_OF_LOOPS / 2) {
                if (RandomUtil::randomFloat(0.0, 1.0) >
                    Config::FAILURE_CHANCE) {
                    std::cout << "Host " << host->addr << " failed"
                              << "\n";
                    host->failed = true;
                }
            }

            host->processLoop();
        }

        std::cout << std::endl;
    }

    for (auto& host : hosts) {
        delete host;
    }
    delete network;
}