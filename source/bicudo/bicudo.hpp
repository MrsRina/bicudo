#ifndef BICUDO_H
#define BICUDO_H

#include "bicudo/api/util/math.hpp"
#include "bicudo/api/util/flag.hpp"
#include "bicudo/core/profile.hpp"
#include "bicudo/api/surface/native.hpp"

namespace bicudo {
    /* The profile core of Bicudo. */
    extern bicudo::profile* core;

    /*
     * Init bicudo framework.
     */
    void init();

    /*
     * Create feature (component, surface, event)
     */
    void create(bicudo::feature*);

    /*
     * Destroy feature (component, surface, event)
     */
    void destroy(bicudo::feature*);
}

#endif