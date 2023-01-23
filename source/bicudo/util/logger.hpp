#ifndef BICUDO_UTIL_LOG_H
#define BICUDO_UTIL_LOG_H

#include <iostream>

namespace bicudo {
    bool log(std::string_view message);
    bool warning(std::string_view message);
    bool exception(std::string_view message);
}

#endif