#include "bicudo/api/util/file.hpp"
#include "bicudo/bicudo.hpp"
#include <fstream>

bool bicudo::readfile(std::string_view path, std::string &string_builder) {
    std::ifstream ifs {path.data()};

    if (ifs.is_open()) {
        std::string string_buffer {};

        while (std::getline(ifs, string_buffer)) {
            string_builder += '\n';
            string_builder += string_buffer;
        }

        ifs.close();
        return true;
    } else {
        std::string log {"Failed to read '"};
        log += path;
        log += "'!";
        bicudo::core->get_logger()->send_warning(log);
    }

    return false;
}

bool bicudo::readfile(std::string_view path, std::vector<int32_t> &bytes) {
    // todo: read file bytes.
    return false;
}