#include "bicudo/direct/display.hpp"
#include "bicudo/util/logger.hpp"

SDL_Window *&bicudo::display::root() {
    return this->p_root;
}

void bicudo::display::on_update() {
    if (this->p_root == nullptr) {
        auto *p_context_overview {bicudo::kernel::p_core->servicedisplay.get_context_overview()};
        this->p_root = SDL_CreateWindow(this->p_initial_title, this->rect[0], this->rect[1], this->rect[2], this->rect[3], p_context_overview->get_api_window_context_flag());
    }
}