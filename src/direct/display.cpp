#include "bicudo/direct/display.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/bicudo.hpp"

int32_t &bicudo::display::id() {
    return this->display_id;
}

SDL_Window *&bicudo::display::root() {
    return this->p_root;
}