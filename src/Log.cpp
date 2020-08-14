#include "Log.hpp"

#include <iostream>

#include "Config.hpp"
#include "string"

Log* Log::instance = nullptr;

Log* Log::getInstance() {
    if (instance == nullptr) {
        instance = new Log();
    }

    return instance;
}

void Log::write(std::string message) {
    file.open(Config::LOG_FILE, std::ios_base::app);

    file << message << "\n";

    file.close();
}