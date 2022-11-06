#include "bicudo/api/util/log.hpp"

void bicudo::print(std::string_view input) {
    std::cout << input.data() << '\n';
}