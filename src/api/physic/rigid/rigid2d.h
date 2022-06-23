#ifndef RIGID_DATA_H
#define RIGID_DATA_H

#include "api/physic/util/physic_util.h"

/**
 * Rigid data.
 **/
class rigid2d {
protected:
    rigid::type type;
    rigid::physic physic;
public:
    math::vec2 center, velocity, acceleration;

    float angle, angular_velocity, angular_acceleration;
    float mass, friction, restitution, inertia;
    float minx, maxx, miny, maxy;

    rigid::type get_type();

    void set_physic(rigid::physic val_enum);
    rigid::physic get_physic();

    bool collide_ab_with(rigid2d* &r);
    bool collide_axis_with(rigid2d* &r);

    virtual void move(math::vec2 vec_vel) {};
    virtual void rotate(float val_angle) {};
    virtual void on_update_position() {};
};

#endif
