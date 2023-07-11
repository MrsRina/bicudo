#ifndef BICUDO_NATIVE_DISPLAY_H
#define BICUDO_NATIVE_DISPLAY_H

#include <iostream>
#include <SDL2/SDL_video.h>
#include "bicudo/util/math.hpp"

namespace bicudo {
    class display {
    protected:
        SDL_Window *p_root {};
    public:
        std::string title {};
        float opacity {1.0f};
        bicudo::vec4 rect {static_cast<float>(SDL_WINDOWPOS_CENTERED), static_cast<float>(SDL_WINDOWPOS_CENTERED), 0.0f, 0.0f};
        uint32_t flags {};
    public:
        SDL_Window *&root();
        void on_update();
    };
}

#endif