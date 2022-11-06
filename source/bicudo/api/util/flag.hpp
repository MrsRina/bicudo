#ifndef BICUDO_API_UTIL_FLAG_H
#define BICUDO_API_UTIL_FLAG_H

#include <iostream>

namespace bicudo {
    extern float const centered;

    /* except this namespace, others will not have double namespaces */
    namespace bitwise {
        uint16_t &set(uint16_t&, uint16_t);
        uint16_t &remove(uint16_t&, uint16_t);
        bool contains(uint16_t&, uint16_t);
    };
};

#endif