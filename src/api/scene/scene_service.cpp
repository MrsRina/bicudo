#include "scene_service.h"

scene* scene_service::get_current_scene() {
    return this->current_scene;
}

void scene_service::start_scene(scene* raw_scene) {
    if (this->current_scene != nullptr && raw_scene != nullptr && this->current_scene->get_name() == raw_scene->get_name()) {
        delete raw_scene;
        return;
    }

    if (raw_scene == nullptr && this->current_scene != nullptr) {
        this->end_scene(this->current_scene);
        return;
    }

    this->current_scene = raw_scene;
    this->current_scene->on_start();
    this->current_scene->set_visibility_flag(util::visibility::VISIBLE);

    util::log(raw_scene->get_name() + " set to current scene.");
}

void scene_service::end_scene(scene* raw_scene) {
    if (this->current_scene == nullptr) {
        return;
    }

    this->current_scene->on_end();
    this->current_scene->set_visibility_flag(util::visibility::LOW_PRIORITY);

    delete this->current_scene;
    this->current_scene = nullptr;

    util::log(raw_scene->get_name() + " unset to current scene.");
}

void scene_service::on_start() {
    service::on_start();
}

void scene_service::on_end() {
    service::on_end();
}

void scene_service::on_event(SDL_Event &sdl_event) {
    if (this->current_scene != nullptr) {
        this->current_scene->on_event(sdl_event);
    }
}

void scene_service::on_locked_update() {
    if (this->current_scene != nullptr) {
        this->current_scene->on_locked_update();
    }
}

void scene_service::on_update() {
    if (this->current_scene != nullptr) {
        this->current_scene->on_update();
    }
}

void scene_service::on_render() {
    if (this->current_scene != nullptr) {
        this->current_scene->on_render();
    }
}