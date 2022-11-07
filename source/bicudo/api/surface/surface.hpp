#ifndef BICUDO_API_SURFACE_H
#define BICUDO_API_SURFACE_H

#include "bicudo/api/feature/feature.hpp"
#include "bicudo/api/geometry/rect.hpp"
#include <SDL2/SDL.h>

namespace bicudo {
    class surface : public bicudo::feature {
    public:
        SDL_Window* root {};
        const char* tag {};
        bicudo::rect rect {};
    };
}

#endif