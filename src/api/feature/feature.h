#pragma once
#include "includes/includes.h"

#ifndef FEATURE
#define FEATURE

/**
 * Feature class to every synchronized object in game.
 **/
class ifeature {
protected:
    uint32_t feature_id;
public:
    ifeature();
    ~ifeature();

    /* Start of setter and getter. */
    void set_feature_id(uint32_t id);
    uint32_t get_feature_id();
    /* End of setter and getter. */

    /* Start of abstract methods. */
    virtual void on_locked_update(uint64_t delta);
    virtual void on_update(uint64_t delta);
    virtual void on_render(float render_time);
    /* End of abstract methods. */
};

#endif