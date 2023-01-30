#ifndef BICUDO_SERVICE_SCENE_SERVICE_H
#define BICUDO_SERVICE_SCENE_SERVICE_H

#include "../feature/service.hpp"
#include "../direct/scene.hpp"

namespace bicudo {
    class service_scene : public service<bicudo::scene*> {
    protected:
        bicudo::feature<bicudo::scene*> *p_current_scene {};
    public:
        void add(bicudo::feature<bicudo::scene*> *p_feature) override;

        void on_native_event(SDL_Event &sdl_event);
        void on_native_update();
        void on_native_render();
    };
}

#endif