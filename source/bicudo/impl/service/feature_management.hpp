#ifndef BICUDO_IMPL_SERVICE_FEATURE_MANAGEMENT_H
#define BICUDO_IMPL_SERVICE_FEATURE_MANAGEMENT_H

#include <vector>
#include <map>
#include "bicudo/api/module/module.hpp"
#include "bicudo/api/scene/scene.hpp"

namespace bicudo {
    class feature_management {
    protected:
        std::vector<bicudo::module*> loaded_module_list {};
        std::vector<bicudo::scene*> loaded_scene_list {};
        std::map<int32_t, uint64_t> registry {};

        int32_t token {};
    public:
        void add_module(bicudo::module*);
        void add_scene(bicudo::scene*);


    };
}

#endif