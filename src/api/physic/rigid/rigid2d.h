#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"
#include "rigid.h"

#ifndef RIGID2D_H
#define RIGID2D_H

/**
 * Rigid class to all rigid objects.
 **/
class rigid2d : public rigid {
public:
    math::vec2 current_pos;
    math::vec2 previous_pos;
    math::vec2 motion;

    float radius;
    float mass;

    rigid2d();
    rigid2d(float val_radius, float val_mass);

    ~rigid2d() {}

    /* Start of setters and getters. */
    void set_pos(float x, float y);
    
    float get_x();
    float get_y();
    /* End of setters and getters. */

    /* Start of override methods. */
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    /* End of override methods. */
};

#endif