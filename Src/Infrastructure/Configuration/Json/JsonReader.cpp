#include "JsonReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Infrastructure::Configuration {

    std::string JsonReader::read() const {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open JSON file: " + filePath);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

}
