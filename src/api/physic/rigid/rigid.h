#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"

#ifndef RIGID_H
#define RIGID_H

/**
 * Rigid class to all rigid objects.
 **/
class rigid : public ifeature {
public:
    math::vec2 pos;
    math::vec2 previous_pos;
    math::vec2 motion;

    float radius;
    float mass;

    rigid();
    rigid(float val_radius, float val_mass);

    ~rigid() {}

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    void on_render();
    /* End of override methods. */
};

#endif