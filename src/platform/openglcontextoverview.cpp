#include "bicudo/platform/openglcontextoverview.hpp"

void bicudo::openglcontextoverview::set_opengl_property(uint32_t minor, uint32_t major, const char *_p_glsl_version) {
    this->minor_opengl_version = minor;
    this->major_opengl_version = major;
    this->p_glsl_version = _p_glsl_version;
}

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

void bicudo::openglcontextoverview::destroy(SDL_Window *p_sdl_window) {
    SDL_GL_DeleteContext(this->sdl_opengl_context);
}