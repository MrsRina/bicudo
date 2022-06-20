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

            if (rigid_obj->no_gravity) {
                continue;
            }

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

    if (!r2->no_gravity) {
        r2->move(correction_amount * r2_mass);
    }

    r1->velocity = math::vec2(0, 0);
//
    //math::vec2 n = geometry::collision_info.normal;
    //math::vec2 start = geometry::collision_info.start * (r2->mass / (r1->mass + r2->mass));
    //math::vec2 end = geometry::collision_info.end * (r1->mass / (r1->mass + r2->mass));
    //math::vec2 p = start + end;
//
    //math::vec2 s1 = p - r1->center;
    //math::vec2 s2 = p - r2->center;
//
    //math::vec2 v1 = r1->velocity + math::vec2(-1 * r1->angular_velocity * s1.y, r1->angular_velocity * s1.x);
    //math::vec2 v2 = r2->velocity + math::vec2(-1 * r2->angular_velocity - s2.y, r2->angular_velocity * s2.x);
    //math::vec2 diff = v2 - v1;
//
    //float diff_normal = diff.dot(n);
    //float new_friction = std::min(r1->friction, r2->friction);
    //float s1_cross = s1.cross(n);
    //float s2_cross = s2.cross(n);
//
    //float new_restituion = std::min(r1->restituion, r2->restituion);
    //float jn = -(1 + new_restituion) * diff_normal;
    //jn = jn / (r1->mass + r2->mass + s1_cross * s1_cross * r1->inertia + s2_cross * s2_cross * r2->inertia);
//
    //r1->angular_velocity -= s1_cross * jn * r1->inertia;
    //r2->angular_velocity += s2_cross * jn * r2->inertia;
}

void physic_service::rigid2d_resolve_collision(rigid2d *&r1, rigid2d *&r2) {
    if (r1->mass == 0 && r2->mass == 0) {
        return;
    }

    if (this->setting_flag_positional_correction_flag) {
        this->rigid2d_positional_correction(r1, r2);
    }
}

