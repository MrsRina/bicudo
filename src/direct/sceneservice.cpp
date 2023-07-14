#include "bicudo/direct/sceneservice.hpp"

int64_t bicudo::sceneservice::find(int32_t id) {
    for (uint64_t it {}; it < this->features.size(); it++) {
        if (this->features.at(it)->id() == id) {
            return static_cast<int64_t>(it);
        }
    }

    return -1;
}

bicudo::scene *bicudo::sceneservice::get(int32_t index) {
    return this->features.at(index);
}

void bicudo::sceneservice::add(bicudo::scene *p_scene) {
    auto &scene_id {p_scene->id()};
    if (this->find(scene_id) == -1) {
        scene_id = ++this->highest_token;
        this->features.emplace_back(p_scene);
    }
}