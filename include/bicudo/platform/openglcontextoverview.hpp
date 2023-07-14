#ifndef BICUDO_OPENGL_CONTEXT_OVERVIEW_H
#define BICUDO_OPENGL_CONTEXT_OVERVIEW_H

#include "contextoverview.hpp"

namespace bicudo {
    class openglcontextoverview : public contextoverview {
    public:
        explicit openglcontextoverview(uint32_t minor, uint32_t major, const char *_p_glsl_version) {
            this->minor_opengl_version = minor;
            this->major_opengl_version = major;
            this->p_glsl_version = _p_glsl_version;
        }

        uint16_t get_api_window_context_flag() override;
        void create(SDL_Window *p_sdl_window) override;
        void destroy(SDL_Window *p_sdl_window) override;
    }; 
}

#endif