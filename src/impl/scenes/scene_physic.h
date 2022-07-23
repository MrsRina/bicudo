#pragma once

#include "api/scene/scene.h"
#include "api/physic/rigid/rigid2d.h"

#ifndef SCENE_PHYSIC_H
#define SCENE_PHYSIC_H

class scene_physic : public scene {
public:
    static scene_physic *instance;

    rigid2d* rigid_object = nullptr;
    rigid2d* player;

    float cx, cy, x, y, prev_x, prev_y;
    bool moving;

    scene_physic() {
        instance = this;

        // Registry this scene.
        this->registry("scene-physic", "Scene to work with physic.");
    }

    ~scene_physic() {
        instance = nullptr;
    }

    void on_start() override;
    void on_end() override;
    void on_event(SDL_Event &sdl_event) override;
    void on_locked_update() override;
    void on_update() override;
    void on_render() override;
};

#endif