#include "bicudo/api/module/module.hpp"

void bicudo::module::set_enabled(bool state) {
    this->enabled = state;
}

bool bicudo::module::is_enabled() {
    return this->enabled;
}
