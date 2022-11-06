#include "bicudo/api/util/flag.hpp"

float const bicudo::centered {-100};

uint16_t &bicudo::bitwise::set(uint16_t &data, uint16_t target) {
    return (data |= target);
}

uint16_t &bicudo::bitwise::remove(uint16_t &data, uint16_t target) {
    return (data &= ~(target));
}

bool bicudo::bitwise::contains(uint16_t &data, uint16_t target) {
    return data & target;
}
