#pragma once

#include <string>

#include "Address.hpp"

class Config {
   public:
    inline static const std::string TEST_FILE = "../tests/large.txt";
    inline static const unsigned int NUMBER_OF_LOOPS = 10;
    inline static const unsigned int T_FAIL = 10;
    inline static const unsigned int T_DELETE = 20;
};