#include "bicudo/util/logger.hpp"

bool bicudo::log(std::string_view message) {
    std::cout << "[B]icudo.Log: " << message << '\n';
    return false;
}

bool bicudo::warning(std::string_view message) {
    std::cout << "[B]icudo.Warning: " << message << '\n';
    return false;
}

bool bicudo::exception(std::string_view message) {
    std::cout << "[B]icudo.Exception: " << message << '\n';
    return true;
}
