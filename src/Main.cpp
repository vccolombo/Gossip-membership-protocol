#include <fstream>
#include <vector>

#include "Config.hpp"
#include "Host.hpp"
#include "Log.hpp"
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

    for (size_t round = 1; round <= Config::NUMBER_OF_ROUNDS; round++) {
        Log::getInstance()->write("Starting round " + std::to_string(round));

        network->dispatchMessages();

        for (auto& host : hosts) {
            if (round == Config::NUMBER_OF_ROUNDS / 2) {
                if (RandomUtil::randomFloat(0., 1.) <
                    Config::HOST_FAILURE_CHANCE) {
                    Log::getInstance()->write("Host " + host->addr + " failed");
                    host->failed = true;
                }
            }

            host->processLoop();
        }
    }

    Log::getInstance()->write("Ending simulation");

    for (auto& host : hosts) {
        delete host;
    }
    delete network;
}