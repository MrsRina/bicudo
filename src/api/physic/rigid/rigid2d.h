#ifndef RIGID_DATA_H
#define RIGID_DATA_H

#include "api/physic/util/physic_util.h"

/**
 * Rigid data.
 **/
class rigid2d {
protected:
    rigid::type type;
public:
    math::vec2 center, velocity, acceleration;

    float angle, angular_velocity, angular_acceleration;
    float mass, friction, restitution, inertia;
    float minx, maxx, miny, maxy;

    /* Start of setters and getters. */
    rigid::type get_type();

    bool collide_ab_with(rigid2d* &r);
    bool collide_axis_with(rigid2d* &r);
    /* End of setters and getters. */

    /* Start of abstract methods. */
    virtual void move(math::vec2 vec_vel) {};
    virtual void rotate(float val_angle) {};
    virtual void on_update_position() {};
    /* End of abstract methods. */
};

#endif
