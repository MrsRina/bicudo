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

    float r1_mass {}, r2_mass {}, r1r2_ndot {}, r1_cross {}, r2_cross {};
    float jn {}, jt {}, num {}, restitution {}, friction {};

    bicudo::vec2 energy {}, resolve_dir {}, n {}, start {}, end, p {}, empty {};
    bicudo::vec2 r1_dir {}, r2_dir {}, r1_vel {}, r2_vel {}, r1r2_vel_dir {};

    for (auto &r1 : this->loaded_rigid_list) {
        for (auto &r2 : this->loaded_rigid_list) {
            if (r1->get_id() != r2->get_id() && (r1->mass != 0.0f || r2->mass != 0.0f)  && bicudo::check_collide_mask(r1, r2) && bicudo::check_collideinfo(this->collideinfo, r1, r2)) {
                /* move r1 & r2 based on normal scaled by depth mass */
                r1_mass = r1->mass;
                r2_mass = r2->mass;

                num = this->collideinfo.depth / (r1_mass + r2_mass) * 1.0f;
                resolve_dir = this->collideinfo.normal * num;

                /* move r2 from r1 oposite */
                r1->update_position(resolve_dir * -r1_mass);
                r2->update_position(resolve_dir * r2_mass);

                n = this->collideinfo.normal;
                start = this->collideinfo.start * (r2_mass / (r1_mass + r2_mass));
                end = this->collideinfo.end * (r1_mass / (r1_mass + r2_mass));
                p = start + end;

                r1_dir = p - r1->pos;
                r2_dir = p - r2->pos;

                r1_vel = r1->velocity;
                empty.x = -1.0f * r1->angular_velocity * r1_dir.y;
                empty.y = r1->angular_velocity * r1_dir.x;
                r1_vel = r1_vel * empty;

                r2_vel = r2->velocity;
                empty.x = -1.0f * r2->angular_velocity * r2_dir.y;
                empty.y = r2->angular_velocity * r2_dir.x;
                r2_vel = r2_vel * empty;

                r1r2_vel_dir = r2_vel - r1_vel;
                r1r2_ndot = bicudo::dot(r1r2_vel_dir, n);
                if (r1r2_ndot > 0.0f) {
                    continue;
                }

                restitution = std::min(r1->restitution, r2->restitution);
                friction = std::min(r1->friction, r2->friction);

                r1_cross = bicudo::cross(r1_dir, n);
                r2_cross = bicudo::cross(r2_dir, n);

                jn = -(1.0f + restitution) * r1r2_ndot;
                jn /= (r1_mass + r2_mass + r1_cross * r1_cross * r1->inertia + r2_cross * r2_cross * r2->inertia);

                energy = n * jn;
                r1->velocity -= energy * r1_mass;
                r2->velocity += energy * r2_mass;

                r1->angular_velocity -= r1_cross * jn * r1->inertia;
                r2->angular_velocity += r2_cross * jn * r2->inertia;

                bicudo::vec2 tangent = r1r2_vel_dir - n * bicudo::dot(r1r2_vel_dir, n);
                tangent = bicudo::normalize(tangent) * -1.0f;

                jt = -(1.0f + restitution) * bicudo::dot(r1r2_vel_dir, tangent) * friction;
                jt /= (r1_mass + r2_mass + r1_cross * r1_cross + r1_mass + r2_cross * r2_cross * r2->inertia);
                jt = jt > jn ? jn : jt;
                
                energy = tangent * jt;
                r1->velocity -= energy * r1_mass;
                r2->velocity += energy * r2_mass;

                r1->angular_velocity -= r1_cross * jt * r1->inertia;
                r2->angular_velocity += r2_cross * jt * r2->inertia;
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
