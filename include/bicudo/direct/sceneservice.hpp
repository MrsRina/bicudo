#ifndef BICUDO_DIRECT_SCENE_SERVICE_H
#define BICUDO_DIRECT_SCENE_SERVICE_H

#include "scene.hpp"
#include "bicudo/service/service.hpp"

namespace bicudo {
    class sceneservice : public service<bicudo::scene*, int32_t> {
    public:
        void add(bicudo::scene *p_scene) override;
    }
}

#endif