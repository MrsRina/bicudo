#ifndef BICUDO_DIRECT_SCENE_SERVICE_H
#define BICUDO_DIRECT_SCENE_SERVICE_H

#include "scene.hpp"
#include <vector>

namespace bicudo {
    class sceneservice {
    protected:
        std::vector<bicudo::scene*> loaded_scene_list {};
        int32_t highest_token;
    public:
        bicudo::scene *p_current_scene {};
    public:
        void start(bicudo::scene *p_scene, bool reload);
        int64_t find(int32_t id);
        bicudo::scene *get(int32_t index);
        void add(bicudo::scene *p_scene);
        void on_shutdown();
    };
}

#endif