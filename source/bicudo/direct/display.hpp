#ifndef BICUDO_NATIVE_DISPLAY_H
#define BICUDO_NATIVE_DISPLAY_H

#include <iostream>
#include <SDL2/SDL_video.h>

namespace bicudo {
    class display {
    protected:
        SDL_Window *p_root {};
    public:
        std::string title {};
        float opacity {1.0f};
        int32_t rect[4] {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0};
        uint32_t flags {};
    public:
        SDL_Window *&root();
        void on_update();
    };
}

#endif