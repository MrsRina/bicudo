#ifndef BICUDO_DIRECT_SCENE_H
#define BICUDO_DIRECT_SCENE_H

#include "bicudo/platform/platform.hpp"

namespace bicudo {
    class scene {
    protected:
        int32_t scene_id {};
    public:
        int32_t &id();
        bool is_loaded();
    public:
        virtual void on_reload();
        virtual void on_create();
        virtual void on_destroy();
        virtual void on_update();
        virtual void on_event(SDL_Event &sdl_event);
        virtual void on_render();
    };
}

#endif