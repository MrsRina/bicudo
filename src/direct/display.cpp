#include "bicudo/direct/display.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/bicudo.hpp"

int32_t &bicudo::display::id() {
    return this->display_id;
}

SDL_Window *&bicudo::display::root() {
    return this->p_root;
}

void bicudo::display::set_display_property(bicudo::displayproperty &display_property) {
    bicudo::kernel::p_core->p_display_service->update(display_property, this);
}