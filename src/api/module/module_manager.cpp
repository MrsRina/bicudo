#include "module_manager.h"

module* module_manager::get_module_by_name(const std::string &name) {
    for (module* modules : this->element_list) {
        if (modules->get_name() == name) {
            return modules;
        }
    }

    return NULL;
}

module* module_manager::get_module_by_feature_id(uint32_t feature_id) {
    for (module* modules : this->element_list) {
        if (modules->get_feature_id() == feature_id) {
            return modules;
        }
    }

    return NULL;
}

void module_manager::on_start() {

}

void module_manager::on_end() {

}

void module_manager::on_event(SDL_Event sdl_event) {

}

void module_manager::on_locked_update(uint64_t delta) {

}

void module_manager::on_update(uint64_t delta) {

}

void module_manager::on_render(float render_time) {
    
}