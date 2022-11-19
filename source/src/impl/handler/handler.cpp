#include "bicudo/bicudo.hpp"

void bicudo::handler::append_module(bicudo::module *feature) {
    this->loaded_module_list.push_back(feature);
}

void bicudo::handler::append_scene(bicudo::scene *feature) {
    this->loaded_scene_list.push_back(feature);
}

void bicudo::handler::set_current_scene(bicudo::scene *feature) {
    if (feature != nullptr && this->current_scene == nullptr) {
        this->current_scene = feature;
        bicudo::core->get_custom_gc().create(this->current_scene);
    } else if (feature != nullptr && this->current_scene != nullptr && feature != this->current_scene) {
        bicudo::core->get_custom_gc().destroy(this->current_scene);
        this->current_scene = feature;
        bicudo::core->get_custom_gc().create(feature);
    }
}

bicudo::scene *bicudo::handler::get_scene_by_tag(std::string_view) {
    return nullptr;
}

bicudo::scene *bicudo::handler::get_scene_by_id(int32_t) {
    return nullptr;
}

bicudo::module *bicudo::handler::get_module_by_tag(std::string_view) {
    return nullptr;
}

bicudo::module *bicudo::handler::get_module_by_id(int32_t) {
    return nullptr;
}

void bicudo::handler::on_event(bicudo::event &event) {
    if (this->current_scene != nullptr) {
        this->current_scene->on_event(event);
    }
}

void bicudo::handler::on_native_update() {
    if (this->current_scene != nullptr) {
        this->current_scene->on_update();
    }
}