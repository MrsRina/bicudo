#ifndef BICUDO_H
#define BICUDO_H

#include "bicudo/direct/display.hpp"
#include "bicudo/direct/scene.hpp"
#include "bicudo/core/core.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/graphics/gpurenderable.hpp"
#include "bicudo/graphics/gpupipeline.hpp"
#include "bicudo/direct/resource/shadergroupresource.hpp"

namespace bicudo {
    namespace kernel {
        extern bicudo::core *p_core;
    }

    void createcore(bicudo::coreproperty &core_property, bicudo::core *p_core);

    void createscene(bicudo::scene *p_scene);
    void startscene(bicudo::scene *p_scene, bool reload = false);
    void createdisplay(bicudo::displayproperty &display_property, bicudo::display *p_display);

    void createasset(bicudo::assetdescriptor &asset_descriptor, bicudo::asset *p_asset);
    bicudo::asset *getasset(std::string_view tag);
}

#endif