#include "scene_service.h"

scene* scene_service::get_current_scene() {
    return this->current_scene;
}

scene* scene_service::get_scene_by_name(const std::string &name) {
    for (scene* &scenes : this->element_list) {
        if (scenes->get_name() == name) {
            return scenes;
        }
    }
}

scene* scene_service::get_scene_by_feature_id(uint32_t feature_id) {
    for (scene* &scenes : this->element_list) {
        if (scenes->get_feature_id() == feature_id) {
            return scenes;
        }
    }

    return NULL;
}

void scene_service::start_scene(scene* raw_scene) {
    if (raw_scene == NULL && this->current_scene != NULL) {
        this->end_scene(this->current_scene);
        return;
    }

    this->current_scene = raw_scene;
    this->current_scene->on_start();
    this->current_scene->set_visibility_flag(util::visibility::VISIBLE);

    util::log(raw_scene->get_name() + " set to current scene.");
}

void scene_service::end_scene(scene* raw_scene) {
    if (this->current_scene == NULL) {
        return;
    }

    this->current_scene->on_end();
    this->current_scene->set_visibility_flag(util::visibility::LOW_PRIORITY);
    this->current_scene = NULL;

    util::log(raw_scene->get_name() + " unset to current scene.");
}