#ifndef BICUDO_DIRECT_SCENE_H
#define BICUDO_DIRECT_SCENE_H

#include "bicudo/platform/platform.hpp"

namespace bicudo {
    class scene {
    public:
        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update();
        virtual void on_event(SDL_Event &sdl_event);
        virtual void on_render();
    };
}

#endif