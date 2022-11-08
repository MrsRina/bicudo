#include "bicudo/api/feature/feature.hpp"

void bicudo::feature::on_create() {

}

void bicudo::feature::on_destroy() {

}

void bicudo::feature::set_id(int32_t feature_id) {
    this->id = feature_id;
}

int32_t bicudo::feature::get_id() {
    return this->id;
}
