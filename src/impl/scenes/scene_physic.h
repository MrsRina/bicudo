#pragma once

#include "api/scene/scene.h"

#ifndef SCENE_PHYSIC_H
#define SCENE_PHYSIC_H

class scene_physic : public scene {
public:
    static scene_physic *instance;

    scene_physic() {
        instance = this;

        // Registry this scene.
        this->registry("scene-physic", "Scene to work with physic.");
    }

    ~scene_physic() {
        instance = nullptr;
    }

    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    void on_render();
};

#endif