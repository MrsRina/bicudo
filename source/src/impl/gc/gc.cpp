#include "bicudo/impl/gc/gc.hpp"

void bicudo::gc::destroy(bicudo::feature *feature) {
    this->features_queue.push(feature);
    this->poll_features_queue = true;
}

void bicudo::gc::create(bicudo::feature *feature) {
    this->features_queue.push(feature);
    this->poll_features_queue = true;
}

bool bicudo::gc::poll() {
    if (this->poll_features_queue) {
        while (!this->features_queue.empty()) {
            auto &feature {this->features_queue.front()};
            this->features_queue.pop();

            if (feature == nullptr) {
                continue;
            }

            if (feature->is_dead()) {
                feature->on_destroy();
                delete feature;
                feature = nullptr;
            } else if (!feature->is_dead() && !feature->is_initialised()) {
                feature->on_create();
            }
        }

        return true;
    }

    return false;
}
