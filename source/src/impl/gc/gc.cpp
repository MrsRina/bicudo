#include "bicudo/impl/gc/garbage_collector.hpp"
#include "bicudo/api/util/log.hpp"

void bicudo::garbage_collector::destroy(bicudo::feature *feature) {
    this->features_queue.push(feature);
    this->poll_features_queue = true;
}

void bicudo::garbage_collector::create(bicudo::feature *feature) {
    this->features_queue.push(feature);
    this->poll_features_queue = true;
}

void bicudo::garbage_collector::on_native_update() {
    if (this->poll_features_queue) {
        while (!this->features_queue.empty()) {
            auto &feature {this->features_queue.back()};
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

        this->poll_features_queue = false;
    }
}
