#ifndef BICUDO_UTIL_FILE_H
#define BICUDO_UTIL_FILE_H

#include <iostream>

namespace bicudo {
    bool readfile(std::string_view path, std::string &string_builder);
}

#endif