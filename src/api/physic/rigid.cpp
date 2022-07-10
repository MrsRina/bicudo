#include "rigid.h"
#include "api/client/instance.h"

bool rigid2d_rect_collide_with_rect(rigid2d_rectangle* r1, rigid2d_rectangle* r2) {
    bool phase1 = false;
    bool phase2 = false;

    geometry::concurrent_collision_info collision_info_r1;
    phase1 = r1->find_axis_least_penetration(r2, collision_info_r1);

    if (phase1) {
        geometry::concurrent_collision_info collision_info_r2;
        phase2 = r2->find_axis_least_penetration(r1, collision_info_r2);

        if (phase2) {
            if (collision_info_r1.depth < collision_info_r2.depth) {
                math::vec2 vec_depth = collision_info_r1.normal * collision_info_r1.depth;
                geometry::collision_info.set(collision_info_r1.depth, collision_info_r1.normal, collision_info_r1.start - vec_depth);
            } else {
                geometry::collision_info.set(collision_info_r2.depth, collision_info_r2.normal * -1.0f, collision_info_r2.start);
            }
        }
    }

    return phase1 && phase2;
}

void rigid2d_solve_collide(rigid2d *&r1, rigid2d *&r2) {
    if (r1->mass == 0 && r2->mass == 0) {
        return;
    }

    if (bicudo::service_physic().setting_flag_positional_correction_flag) {
        float mass_r1 = r1->mass;
        float mass_r2 = r2->mass;

        float num = geometry::collision_info.depth / (mass_r1 + mass_r2) * bicudo::service_physic().setting_pos_correction_rate;
        math::vec2 vec_correction_amount = geometry::collision_info.normal * num;

        r1->move(vec_correction_amount * -mass_r1);
        r2->move(vec_correction_amount * mass_r2);
    }

    switch (r1->get_physic()) {
        case rigid::FULL: {
            rigid2d_apply_full_physic(r1, r2);
            break;
        }

        case rigid::POS: {
            rigid2d_apply_physic(r1, r2);
            break;
        }
    }
}

bool rigid2d_collide_with_point(rigid2d *&r, float x, float y) {
     bool flag_point_collide = (
            x >= r->minx && y >= r->miny &&
            x <= r->maxx && y <= r->maxy
    );

    return flag_point_collide;
}

void rigid2d_apply_full_physic(rigid2d* &r1, rigid2d* &r2) {
    math::vec2 n = geometry::collision_info.normal;
    math::vec2 start = geometry::collision_info.start * (r2->mass / (r1->mass + r2->mass));
    math::vec2 end = geometry::collision_info.end * (r1->mass / (r1->mass + r2->mass));
    math::vec2 p = start + end;

    math::vec2 c1 = p - r1->center;
    math::vec2 c2 = p - r2->center;

    math::vec2 v1 = r1->velocity + math::vec2(-1.0f * r1->angular_velocity * c1.y, r1->angular_velocity * c1.x);
    math::vec2 v2 = r2->velocity + math::vec2(-1.0f * r2->angular_velocity * c2.y, r2->angular_velocity * c2.x);

    math::vec2 relative_velocity = v2 - v1;
    float relative_velocity_normal = relative_velocity.dot(n);

    if (relative_velocity_normal > 0.0f) {
        return;
    }

    float new_restitution = std::min(r1->restitution, r2->restitution);
    float new_friction = std::min(r1->friction, r2->friction);

    float c1_cross_n = c1.cross(n);
    float c2_cross_n = c2.cross(n);

    float jn = -(1.0f + new_restitution) * relative_velocity_normal;

    jn /= (r1->mass + r2->mass + c1_cross_n * c1_cross_n * r1->inertia + c2_cross_n * c2_cross_n * r2->inertia);
    math::vec2 impulse = n * jn;

    r1->velocity -= impulse * r1->mass;
    r2->velocity += impulse * r2->mass;

    r1->angular_velocity -= c1_cross_n * jn * r1->inertia;
    r2->angular_velocity += c2_cross_n * jn * r2->inertia;

    math::vec2 tangent = relative_velocity - n * relative_velocity.dot(n);
    tangent = tangent.normalize() * -1.0f;

    float c1_cross_t = c1.cross(tangent);
    float c2_cross_t = c2.cross(tangent);

    float jt = -(1.0f + new_restitution) * relative_velocity.dot(tangent) * new_friction;
    jt /= (r1->mass + r2->mass + c1_cross_t * c1_cross_t + r1->mass + c2_cross_t * c2_cross_t * r2->inertia);
    jt = jt > jn ? jn : jt;

    impulse = tangent * jt;

    r1->velocity -= impulse * r1->mass;
    r2->velocity += impulse * r2->mass;

    r1->angular_velocity -= c1_cross_t * jt * r1->inertia;
    r2->angular_velocity += c2_cross_t * jt * r2->inertia;
}

void rigid2d_apply_physic(rigid2d* &r1, rigid2d* &r2) {
    math::vec2 n = geometry::collision_info.normal;
    math::vec2 v1 = r1->velocity;
    math::vec2 v2 = r2->velocity;
    math::vec2 relative_velocity = v2 - v1;

    float relative_velocity_normal = relative_velocity.dot(n);

    if (relative_velocity_normal > 0.0f) {
        return;
    }

    float new_restitution = std::min(r1->restitution, r2->restitution);
    float new_friction = std::min(r1->friction, r2->friction);
    float jn = -(1.0f + new_restitution) * relative_velocity_normal;

    jn /= (r1->mass + r2->mass);
    math::vec2 impulse = n * jn;

    r1->velocity -= impulse * r1->mass;
    r2->velocity += impulse * r2->mass;

    math::vec2 tangent = relative_velocity - n * relative_velocity.dot(n);
    tangent = tangent.normalize() * -1.0f;

    float jt = -(1.0f + new_restitution) * relative_velocity.dot(tangent) * new_friction;
    jt /= r1->mass + r2->mass;
    jt = jt > jn ? jn : jt;

    impulse = tangent * jt;

    r1->velocity -= impulse * r1->mass;
    r2->velocity += impulse * r2->mass;
}