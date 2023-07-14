#ifndef BICUDO_OPENGL_CONTEXT_OVERVIEW_H
#define BICUDO_OPENGL_CONTEXT_OVERVIEW_H

#include "contextoverview.hpp"
#include <iostream>

namespace bicudo {
    class openglcontextoverview : public contextoverview {
    public:
        void set_opengl_property(uint32_t minor, uint32_t major, const char *_p_glsl_version) override;
        uint16_t get_api_window_context_flag() override;
        void create(SDL_Window *p_sdl_window) override;
        void destroy(SDL_Window *p_sdl_window) override;
    }; 
}

#endif