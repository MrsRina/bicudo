#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"
#include "abstract_rigid.h"

#ifndef RIGID2D_H
#define RIGID2D_H

/**
 * Rigid class to all abstract_rigid objects.
 **/
class rigid2d : public abstract_rigid {
public:
    math::vec2 current_pos;
    math::vec2 previous_pos;
    math::vec2 motion;

    float radius;
    float mass;

    rigid2d();
    rigid2d(float val_radius, float val_mass);

    ~rigid2d() {}

    /* Start of override methods. */
    void on_update_gravity();
    void on_update_position();
    /* End of override methods. */
};

#endif