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
    /* Start of setters and getters. */
    void set_type(rigid::type val_type);
    rigid::type get_type();
    /* End of setters and getters. */

    /* Start of abstract methods. */
    virtual void on_update_gravity() {}
    virtual void on_update_position() {}
    /* End of abstract methods. */
};

#endif