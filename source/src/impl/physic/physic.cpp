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

    float r1_mass {}, r2_mass {};
    float num {};
    bicudo::vec2 resolve_dir {};

    for (auto &r1 : this->loaded_rigid_list) {
        for (auto &r2 : this->loaded_rigid_list) {
            if (r1->get_id() != r2->get_id() && (r1->mass != 0.0f || r2->mass != 0.0f)  && bicudo::check_collide_mask(r1, r2) && bicudo::check_collideinfo(this->collideinfo, r1, r2)) {
                r1_mass = r1->mass;
                r2_mass = r2->mass;
                num = this->collideinfo.depth / (r1_mass + r2_mass) * 1.0f;
                resolve_dir = this->collideinfo.normal * num;

                r1->update_position(resolve_dir * -r1_mass);
                r2->update_position(resolve_dir * r2_mass);
            }
        }
    }
}

void bicudo::physic::append(bicudo::rigid *rigid) {
    this->loaded_rigid_list.push_back(rigid);
    rigid->set_id(this->id_token_feature++);
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
