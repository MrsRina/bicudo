#ifndef BICUDO_H
#define BICUDO_H

#include "bicudo/api/util/math.hpp"
#include "bicudo/api/util/flag.hpp"
#include "bicudo/core/profile.hpp"
#include "bicudo/api/shader/shader.hpp"
#include "bicudo/api/surface/surface.hpp"
#include "bicudo/api/util/file.hpp"
#include "bicudo/api/scene/scene.hpp"
#include "bicudo/impl/render/immshape.hpp"

namespace bicudo {
    /* The profile core of Bicudo. */
    extern bicudo::profile *core;

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
    void create(bicudo::shader*, const std::vector<bicudo::resource>&);

    /*
     * Make current scene.
     */
    void makecurrent(bicudo::scene*);

    /*
     * Mainloop Bicudo.
     */
    void mainloop();

    /*
     * Listen input by name and return the state of input.
     */
    bool listen(std::string_view);

    /*
     * Custom garbage collector, make sure what you handle calling this method.
     */
    bicudo::garbage_collector &gc();

    /*
     * Get main log.
     */
    bicudo::logger *log();

    /*
     * Get input service.
     */
    bicudo::input *getinput();
}

#endif