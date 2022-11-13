#ifndef BICUDO_IMPL_SERVICE_FEATURE_MANAGEMENT_H
#define BICUDO_IMPL_SERVICE_FEATURE_MANAGEMENT_H

#include <vector>
#include <map>
#include "bicudo/api/module/module.hpp"
#include "bicudo/api/scene/scene.hpp"
#include "bicudo/api/event/event.hpp"

namespace bicudo {
    class handler {
    protected:
        std::vector<bicudo::feature*> loaded_module_list {}, loaded_scene_list {};
        bicudo::scene* current_scene {};
        int32_t token {};
    public:
        void append_module(bicudo::module*);
        void append_scene(bicudo::scene*);
        void set_current_scene(bicudo::scene*);

        bicudo::scene* get_scene_by_tag(std::string_view);
        bicudo::scene* get_scene_by_id(int32_t);

        bicudo::module* get_module_by_tag(std::string_view);
        bicudo::module* get_module_by_id(int32_t);

        void on_event(bicudo::event &event);
        void on_native_update();
    };
}

#endif