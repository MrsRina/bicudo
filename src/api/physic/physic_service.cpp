#include "physic_service.h"
#include "api/physic/rigid/abstract_rigid.h"

void physic_service::update_gravity() {
    abstract_rigid* rigid_obj;

    for (ifeature* &features : this->update_list) {
        rigid_obj = (abstract_rigid*) features;

        if (rigid_obj->no_gravity) {
            continue;
        }

        rigid_obj->on_update_gravity();
    }
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

    for (ifeature* &features : this->update_list) {
        rigid_obj = (abstract_rigid*) features;

        switch (rigid_obj->get_type()) {
            case rigid::type::RIGID2D: {
                for (ifeature* &subfeatures : this->update_list) {
                    if (subfeatures == features) {
                        continue;
                    }

                    switch (rigid_obj->get_type()) {
                        case rigid::type::RIGID2D: {
                            auto rigid2d_obj = (rigid2d*) features;
                            auto sub_rigid2d_obj = (rigid2d*) subfeatures;

                            if (rigid2d_detect_collide(rigid2d_obj, sub_rigid2d_obj)) {

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

void physic_service::process_collision() {
}

