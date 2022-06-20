#include "physic_service.h"
#include "api/physic/rigid/abstract_rigid.h"
#include "api/render/tessellator.h"

void physic_service::update_gravity() {
    abstract_rigid* rigid_obj;
}

void physic_service::update_pos() {
    abstract_rigid* rigid_obj;

    for (ifeature* &features : this->update_list) {
        rigid_obj = (abstract_rigid *) features;
        rigid_obj->on_update_position();
    }
}

void physic_service::on_start() {

}

void physic_service::on_end() {

}

void physic_service::on_event(SDL_Event &sdl_event) {

}

void physic_service::on_locked_update() {
    this->update_gravity();
    this->update_pos();

    abstract_rigid* rigid_obj;

    for (uint8_t i = 0; i < this->setting_iterations_count; i++) {
        for (ifeature* &features : this->update_list) {
            rigid_obj = (abstract_rigid *) features;

            switch (rigid_obj->get_type()) {
                case rigid::type::RIGID2D: {
                    for (ifeature *&subfeatures: this->update_list) {
                        if (subfeatures == features) {
                            continue;
                        }

                        switch (rigid_obj->get_type()) {
                            case rigid::type::RIGID2D: {
                                auto rigid2d_obj = (rigid2d *) features;
                                auto sub_rigid2d_obj = (rigid2d *) subfeatures;

                                if (this->rigid2d_detect_collide(rigid2d_obj, sub_rigid2d_obj)) {
                                    this->rigid2d_resolve_collision(rigid2d_obj, sub_rigid2d_obj);
                                }

                                break;
                            };
                        }
                    }

                    break;
                };
            }
        }
    }
}

void physic_service::on_update() {

}

void physic_service::on_render() {

}

bool physic_service::rigid2d_detect_collide(rigid2d* &r1, rigid2d* &r2) {
    bool phase1 = false;
    bool phase2 = false;

    geometry::concurrent_collision_info collision_info_r1;
    phase1 = r1->find_axis_least_penetration(r2, collision_info_r1);

    if (phase1) {
        geometry::concurrent_collision_info collision_info_r2;
        phase2 = r2->find_axis_least_penetration(r1, collision_info_r2);

        if (phase2) {
            if (collision_info_r1.depth < collision_info_r2.depth) {
                math::vec2 depth_vec = collision_info_r1.normal * collision_info_r1.depth;
                geometry::collision_info.set(collision_info_r1.depth, collision_info_r1.normal, collision_info_r1.start - depth_vec);
            } else {
                geometry::collision_info.set(collision_info_r2.depth, collision_info_r2.normal * -1, collision_info_r2.start);
            }
        }
    }

    return phase1 && phase2;
}

void physic_service::rigid2d_positional_correction(rigid2d* &r1, rigid2d* &r2) {
    float r1_mass = r1->mass;
    float r2_mass = r2->mass;

    float num = geometry::collision_info.depth / (r1_mass + r1_mass) * this->setting_pos_correction_rate;
    math::vec2 correction_amount = geometry::collision_info.normal * num;

    r1->move(correction_amount * -r1_mass);
    r2->move(correction_amount * r2_mass);
}

void physic_service::rigid2d_resolve_collision(rigid2d *&r1, rigid2d *&r2) {
    if (r1->mass == 0 && r2->mass == 0) {
        return;
    }

    if (this->setting_flag_positional_correction_flag) {
        this->rigid2d_positional_correction(r1, r2);
    }


    math::vec2 n = geometry::collision_info.normal;
    math::vec2 v1 = r1->velocity;
    math::vec2 v2 = r2->velocity;
    math::vec2 relative_velocity = v2 - v1;

    float relative_velocity_normal = relative_velocity.dot(n);

    if (relative_velocity_normal > 0) {
        return;
    }

    float new_restituion = std::min(r1->restituion, r2->restituion);
    float new_friction = std::min(r1->friction, r2->friction);
    float jn = -(1.0f + new_restituion) * relative_velocity_normal;
    jn /= (r1->mass + r2->mass);

    math::vec2 impulse = n * jn;

    r1->velocity = r1->velocity - impulse * r1->mass;
    r2->velocity = r2->velocity + impulse * r2->mass;

    math::vec2 tanget = relative_velocity - n * relative_velocity.dot(n);
    tanget = tanget.normalize() * -1.0f;

    float jt = -(1.0f + new_restituion) * relative_velocity.dot(tanget) * new_friction;
    jt = jt / (r1->mass + r2->mass);

    if (jt > jn) {
        jt = jn;
    }

    impulse = tanget * jt;

    r1->velocity = r1->velocity - impulse * r1->mass;
    r2->velocity = r2->velocity + impulse * r2->mass;
}