#include "bicudo/service/service_scene.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::service_scene::add(bicudo::feature<bicudo::scene *> *p_feature) {
    if (p_feature == nullptr) {
        return;
    }

    if (this->p_current_scene != nullptr) {
        this->features.clear();
        this->p_current_scene->content->on_destroy();
        delete this->p_current_scene;
    }

    this->p_current_scene = p_feature;
    this->p_current_scene->content->on_create();
    service::add(p_feature);
    bicudo::log("Just created 1 scene.");
}

void bicudo::service_scene::on_native_update() {
    if (this->p_current_scene != nullptr && this->p_current_scene->content != nullptr) {
        this->p_current_scene->content->on_update();
    }
}

void bicudo::service_scene::on_native_render() {
    if (this->p_current_scene != nullptr && this->p_current_scene->content != nullptr) {
        this->p_current_scene->content->on_render();
    }
}
