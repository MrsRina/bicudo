#include "bicudo/util/file.hpp"
#include "bicudo/util/logger.hpp"
#include <fstream>

bool bicudo::readfile(std::string_view path, std::string &string_builder) {
    std::ifstream ifs {};
    ifs.open(path.data());
    bool flag {};

    if (ifs.is_open()) {
        std::string string_buffer {};
        while (std::getline(ifs, string_buffer)) {
            string_builder += string_buffer;
            string_builder += '\n';
        }
    } else {
        std::string msg {"Failed to read file '"}; msg += path; msg += '\'';
        flag = bicudo::exception(msg);
    }

    ifs.close();
    return flag;
}
