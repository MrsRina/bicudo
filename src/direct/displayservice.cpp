#include "bicudo/direct/displayservice.hpp"

int64_t bicudo::displayservice::find(int32_t id) {
    for (uint64_t it {}; it < this->features.size(); it++) {
        if (this->features.at(it)->id() == id) {
            return static_cast<int64_t>(it);
        }
    }

    return -1;
}

bicudo::display *bicudo::displayservice::get(int32_t index) {
    return this->features.at(index);
}

void bicudo::displayservice::add(bicudo::display *p_display) {
    auto &display_id {p_display->id()};
    if (this->find(display_id) == -1) {
        display_id = ++this->highest_token;
        this->features.emplace_back(p_display);
    }
}

void bicudo::displayservice::update(bicudo::displayproperty &display_property,
                                    bicudo::display *p_display) {
    if (p_display == nullptr || (p_display == nullptr && display_property.p_api_context_overview == nullptr)) {
        return;
    }

    auto &display_root {p_display->root()};
    if (display_root == nullptr) {
        display_root = SDL_CreateWindow("Bicudo", 
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            800, 600, 
            display_property.p_api_context_overview->get_api_window_context_flag()
        );

        display_property.p_api_context_overview->create(display_root);
        p_display->size = {800, 600};
    }

    if (display_property.p_title != nullptr) {
        SDL_SetWindowTitle(display_root, display_property.p_title);
    }

    if (display_property.size.x != -1 && display_property.size.y != -1) {
        SDL_SetWindowSize(display_root, display_property.size.x, display_property.size.y);
        p_display->size = display_property.size;
    }

    if (display_property.fullscreen != -1) {
        SDL_SetWindowFullscreen(display_root, display_property.fullscreen);
    }

    if (display_property.resizable != -1) {
        SDL_SetWindowResizable(display_root, static_cast<SDL_bool>(display_property.resizable));   
    }
}