#ifndef BICUDO_PLATFORM_CONTEXT_OVERVIEW_H
#define BICUDO_PLATFORM_CONTEXT_OVERVIEW_H

#include "platform.hpp"

namespace bicudo {
    class contextoverview {
    protected:
        SDL_GLContext sdl_opengl_context {};

        bool library_was_initialized {};
        const char *p_glsl_version {};

        uint32_t major_opengl_version {};
        uint32_t minor_opengl_version {};
    public:
        explicit contextoverview() = default;

        virtual void set_opengl_property(uint32_t, uint32_t, const char*);
        virtual uint16_t get_api_window_context_flag() { return 0; };
        virtual void create(SDL_Window*) {};
        virtual void destroy(SDL_Window*) {};

        const char *get_glsl_version() {
            return this->p_glsl_version;
        }
    };
}

#endif