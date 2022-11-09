#ifndef BICUDO_H
#define BICUDO_H

#include "bicudo/api/util/math.hpp"
#include "bicudo/api/util/flag.hpp"
#include "bicudo/core/profile.hpp"
#include "bicudo/api/surface/surface.hpp"

namespace bicudo {
    /* The profile core of Bicudo. */
    extern bicudo::profile* core;

    /*
     * Init bicudo framework.
     */
    void init();

    /*
     * Create window surface.
     */
    void create(bicudo::surface*);

    /*
     * Destroy window surface.
     */
    void destroy(bicudo::surface*);

    /*
     * Create shading program (shader).
     */
    void creat(bicudo::shader*, const std::vector<bicudo::shader>&);

    /*
     * Custom garbage collector, make sure what you handle calling this method.
     */
    bicudo::gc &gc();

    /*
     * Get main log.
     */
    bicudo::logger* log();
}

#endif