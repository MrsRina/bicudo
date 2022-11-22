#include "bicudo/impl/physic/physic.hpp"
#include "bicudo/bicudo.hpp"
#include "bicudo/impl/physic/collision.hpp"

void bicudo::physic::on_create() {

}

void bicudo::physic::on_destroy() {

}

void bicudo::physic::on_native_update() {

}

void bicudo::physic::on_native_unsafe_update() {
    for (auto &rigid : this->loaded_rigid_list) {
        rigid->on_update();
    }

    for (auto &r1 : this->loaded_rigid_list) {
        for (auto &r2 : this->loaded_rigid_list) {
            if (r1 != r2 && bicudo::check_collide_mask(r1, r2)) {
                bicudo::print("hiii");
                bool stuff {};
            }
        }
    }
}

void bicudo::physic::append(bicudo::rigid *rigid) {
    this->loaded_rigid_list.push_back(rigid);
    bicudo::core->get_custom_gc().create(rigid);
}

void bicudo::physic::on_native_render() {
    this->immediate_shape.invoke();
    for (auto &rigid : this->loaded_rigid_list) {
        this->immediate_shape.prepare(rigid->min.x, rigid->min.y, rigid->size.x, rigid->size.y, {255, 255, 255, 255});
        this->immediate_shape.draw();
    }

    this->immediate_shape.revoke();
}
