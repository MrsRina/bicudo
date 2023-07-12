#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"
#include <fstream>

bool bicudo::readfile(std::string_view path, std::string &string_builder) {
    std::ifstream ifs {path.data(), std::ifstream::in};
    if (ifs.is_open()) {
        std::string string_buffer {};
        while (std::getline(ifs, string_buffer)) {
            string_builder += string_buffer;
            string_builder += '\n';
        }
        
        ifs.close();
    } else {
        std::string msg {"Failed to read file '"}; msg += path; msg += '\'';
        return true;
    }

    return false;
}