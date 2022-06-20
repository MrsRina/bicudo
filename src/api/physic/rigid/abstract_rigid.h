#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"
#include "api/physic/util/physic_util.h"

#ifndef ABSTRACT_RIGID_H
#define ABSTRACT_RIGID_H

/**
 * Rigid class to all abstract_rigid objects.
 **/
class abstract_rigid : public ifeature {
protected:
    rigid::type type;
public:
    float mass, angle, friction, restituion, inertia, radius, bound_radius;
    bool no_gravity = false;

    math::vec2 center;

    /* Start of setters and getters. */
    void set_type(rigid::type val_type);
    rigid::type get_type();
    /* End of setters and getters. */

    /* Start of abstract methods. */
    virtual void on_update_gravity() {}
    virtual void on_update_position() {}
    virtual void on_center_calc() {}
    /* End of abstract methods. */
};

#endif