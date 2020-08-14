#pragma once

#include <fstream>
#include <string>

#include "Address.hpp"
#include "Config.hpp"

class Log {
    static Log* instance;

    std::ofstream file;

    Log() { remove(Config::LOG_FILE.c_str()); }

   public:
    static Log* getInstance();

    void write(std::string message);
};