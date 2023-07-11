#include "bicudo/service/servicescene.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::servicescene::add(bicudo::feature<bicudo::scene *> *p_feature) {
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

    bicudo::log() << "A scene was created";
}

void bicudo::servicescene::on_native_event(SDL_Event &sdl_event) {
    if (this->p_current_scene != nullptr && this->p_current_scene->content != nullptr) {
        this->p_current_scene->content->on_event(sdl_event);
    }
}

void bicudo::servicescene::on_native_update() {
    if (this->p_current_scene != nullptr && this->p_current_scene->content != nullptr) {
        this->p_current_scene->content->on_update();
    }
}

void bicudo::servicescene::on_native_render() {
    if (this->p_current_scene != nullptr && this->p_current_scene->content != nullptr) {
        this->p_current_scene->content->on_render();
    }
}
