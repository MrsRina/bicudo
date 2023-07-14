#include "bicudo/platform/openglcontextoverview.hpp"

uint16_t bicudo::openglcontextoverview::get_api_window_context_flag() {
    return SDL_WINDOW_OPENGL;
}

void bicudo::openglcontextoverview::create(SDL_Window *p_sdl_window) {
    this->sdl_opengl_context = SDL_GL_CreateContext(p_sdl_window);

    if (!this->library_was_initialized) {
        this->library_was_initialized = true;
        glewExperimental = GL_TRUE;
        glewInit();
    }
}