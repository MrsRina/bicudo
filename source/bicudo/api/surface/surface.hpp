#ifndef BICUDO_API_SURFACE_H
#define BICUDO_API_SURFACE_H

#include "bicudo/api/feature/feature.hpp"
#include "bicudo/api/geometry/rect.hpp"
#include <SDL2/SDL.h>

namespace bicudo {
    class surface : public bicudo::feature {
    public:
        SDL_Window* root {};
        SDL_GLContext context {};

        const char* tag {};
        bicudo::rect rect {};

        uint64_t display_fps {}, locked_fps {60};
        float delta_time {};
        bool fullscreen {}, resizable {}, vsync {};

        void on_create() override;
        void on_destroy() override;
    };
}

#endif