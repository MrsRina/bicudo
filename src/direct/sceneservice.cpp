#include "bicudo/bicudo.hpp"
#include "bicudo/util/logger.hpp"
#include "bicudo/util/logger.hpp"

void bicudo::sceneservice::start(bicudo::scene *p_scene, bool reload) {
    if (p_scene == nullptr) {
        bicudo::log() << "Failed to start scene (nullptr)";
    }

    this->p_current_scene = p_scene;
    if (!reload) {
        return;
    }

    bicudo::kernel::p_core->generate_task() = {
        .p_data   = nullptr,
        .function = [p_scene](void*) {
            p_scene->on_create();
        }
    };
}

int64_t bicudo::sceneservice::find(int32_t id) {
    for (uint64_t it {}; it < this->loaded_scene_list.size(); it++) {
        if (this->loaded_scene_list.at(it)->id() == id) {
            return static_cast<int64_t>(it);
        }
    }

    return -1;
}

bicudo::scene *bicudo::sceneservice::get(int32_t index) {
    return this->loaded_scene_list.at(index);
}

void bicudo::sceneservice::add(bicudo::scene *p_scene) {
    auto &scene_id {p_scene->id()};
    if (this->find(scene_id) == -1) {
        scene_id = ++this->highest_token;
        this->loaded_scene_list.emplace_back(p_scene);

        bicudo::kernel::p_core->generate_task() = {
            .p_data   = nullptr,
            .function = [p_scene](void*) {
                p_scene->on_create();
            }
        };
    }
}

void bicudo::sceneservice::on_shutdown() {
    bicudo::log() << "Scene service shutdown called";
}