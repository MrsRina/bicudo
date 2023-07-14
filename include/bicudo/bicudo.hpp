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

    extern int32_t toplevel;

    void createcore(bicudo::core *p_core);
    void createdisplay(bicudo::display *p_display);
    void setdisplayproperty(bicudo::displayproperty &display_property, bicudo::display *p_display);
}

#endif