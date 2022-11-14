#ifndef BICUDO_API_EVENT_H
#define BICUDO_API_EVENT_H

#include <SDL2/SDL.h>

namespace bicudo {
    struct event {
        SDL_Event *native {nullptr};
    };
}

#endif