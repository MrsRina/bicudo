#include "bicudo/api/feature/feature.hpp"

void bicudo::feature::on_create() {
    this->initialised = true;
}

void bicudo::feature::on_destroy() {
    this->dead = false; // forced
}

void bicudo::feature::set_id(int32_t feature_id) {
    this->id = feature_id;
}

int32_t bicudo::feature::get_id() {
    return this->id;
}

void bicudo::feature::set_dead(bool state) {
    this->dead = state;
}

bool bicudo::feature::is_dead() {
    return this->dead;
}

bool bicudo::feature::is_initialised() {
    return this->initialised;
}
