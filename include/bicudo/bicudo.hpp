#ifndef BICUDO_H
#define BICUDO_H

#include "bicudo/direct/display.hpp"
#include "bicudo/direct/scene.hpp"
#include "bicudo/core/core.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/graphics/gpurenderable.hpp"
#include "bicudo/graphics/gpupipeline.hpp"

namespace bicudo {
    namespace kernel {
        extern bicudo::core *p_core;
    }

    void createcore(bicudo::core *p_core);
    void createdisplay(bicudo::display *p_display);
    void createscene(bicudo::scene *p_scene);
    void startscene(bicudo::scene *p_scene, bool reload = false);
}

#endif