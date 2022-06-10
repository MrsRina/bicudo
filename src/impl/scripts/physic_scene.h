#pragma once

#include "api/scene/scene.h"

#ifndef PHYSIC_SCENE_H
#define PHYSIC_SCENE_H

class physic_scene : public scene {
public:
    static physic_scene *instance;

    physic_scene() {
        instance = this;
    }

    ~physic_scene() {
        instance = nullptr;
    }

    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update(uint64_t delta);
    void on_update(uint64_t delta);
    void on_render(float render_time);
};

#endif