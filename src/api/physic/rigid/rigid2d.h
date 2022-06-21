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
    float mass, friction, restitution;

    /* Start of setters and getters. */
    rigid::type get_type();
    /* End of setters and getters. */

    /* Start of abstract methods. */
    virtual void on_update_position() {};
    /* End of abstract methods. */
};

#endif
