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

        int32_t token {};
    public:
        void add_module(bicudo::module*);
        void add_scene(bicudo::scene*);

        void load_scene(std::string_view);
        bicudo::scene* get_scene_by_tag(std::string_view);
        bicudo::scene* get_scene_by_id(int32_t);

        bicudo::module* get_module_by_tag(std::string_view);
        bicudo::module* get_module_by_id(int32_t);
    };
}

#endif