#ifndef BICUDO_NATIVE_DISPLAY_H
#define BICUDO_NATIVE_DISPLAY_H

#include <iostream>
#include <SDL2/SDL_video.h>
#include "bicudo/util/math.hpp"

namespace bicudo {
    class display {
    protected:
        const char *p_initial_title {};
        SDL_Window *p_root {};
        uint16_t context_api {}
    public:
        bicudo::vec4 rect {static_cast<float>(SDL_WINDOWPOS_CENTERED), static_cast<float>(SDL_WINDOWPOS_CENTERED), 0.0f, 0.0f};
    public:
        explicit display(const char *p_title) : p_initial_title(p_title) {};        
        SDL_Window *&root();
        void on_update();
    };
}

#endif