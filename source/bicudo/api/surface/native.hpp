#ifndef BICUDO_API_SURFACE_NATIVE_H
#define BICUDO_API_SURFACE_NATIVE_H

#include "surface.hpp"
#include <SDL2/SDL.h>

namespace bicudo {
    class surface_native : public bicudo::surface {
        SDL_Window* root {};
    };
}

#endif