#pragma once

#include <string>

#include "Address.hpp"

class Config {
   public:
    inline static const std::string TEST_FILE = "../tests/large.txt";
    inline static const std::string LOG_FILE = "../logs/large.log";
    inline static const unsigned int NUMBER_OF_LOOPS = 100;
    inline static const unsigned int T_FAIL = 10;
    inline static const unsigned int T_DELETE = 20;
    inline static const float FAILURE_CHANCE = 0.5;
    inline static const float MSG_DROP_CHANCE = 0.5;
};