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
                                process_collision();
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

bool physic_service::rigid2d_detect_collide(rigid2d* r1, rigid2d* r2) {
    geometry::edge* edge = nullptr;
    math::vec2 axis;
    rigid2d* parent = nullptr;

    float min_len = 10000.0f;
    float min_dist = 10000.0f;
    float dist = 0.0f;

    for (uint8_t i = 0; i < r1->get_edge_count() + r2->get_edge_count(); i++) {
        if (i < r1->get_edge_count()) {
            edge = r1->get_edges()[i];
        } else {
            edge = r2->get_edges()[i - r1->get_edge_count()];
        }

        axis.x = edge->v1->position.y - edge->v2->position.y;
        axis.y = edge->v2->position.x - edge->v1->position.x;
        axis = axis.normalize();

        float min_a, min_b, max_a, max_b;

        r1->project_to_axis(axis, min_a, max_a);
        r2->project_to_axis(axis, min_b, max_b);

        dist = rigid::interval_dist(min_a, max_a, min_b, max_b);

        if (dist > 0.0f) {
            return false;
        } else if (abs(dist) < min_dist) {
            min_dist = abs(dist);

            geometry::collision_info.normal = axis;
            geometry::collision_info.e = edge;

            parent = i < r1->get_edge_count() ? r1 : r2;
        }
    }

    geometry::collision_info.depth = min_dist;

    if (parent != r2) {
        parent = r2;

        r2 = r1;
        r1 = parent;
    }

    int32_t sign = (int) (geometry::collision_info.normal * (r1->center - r2->center));

    if (sign != 1)
        geometry::collision_info.normal = -geometry::collision_info.normal;

    float smallest_dist = 10000.0f;
    dist = 0.0f;

    for (uint8_t i = 0; i < r1->get_vertex_count(); i++) {
        dist = geometry::collision_info.normal * (r1->get_vertices()[i]->position - r2->center);

        if (dist < smallest_dist) {
            smallest_dist = dist;
            geometry::collision_info.v = r1->get_vertices()[i];
        }
    }

    return true;
}

void physic_service::process_collision() {
    math::vec2 collision = geometry::collision_info.normal * geometry::collision_info.depth;

    geometry::vertex* e1 = geometry::collision_info.e->v1;
    geometry::vertex* e2 = geometry::collision_info.e->v2;

    float t;

    if (abs(e1->position.x - e2->position.x) > abs(e1->position.y - e2->position.y)) {
        t = (geometry::collision_info.v->position.x - collision.x - e1->position.x) / (e2->position.x - e1->position.x);
    } else {
        t = (geometry::collision_info.v->position.y - collision.y - e1->position.y) / (e2->position.y - e1->position.y);
    }

    float lambda = 1.0f / (t*t + (1 - t) * (1 - t));

    e1->position -= collision * (1 - t) * 0.5f * lambda;
    e2->position -= collision * t * 0.5f * lambda;

    geometry::collision_info.v->position += collision * 0.5f;
}

void physic_service::add_vertex(geometry::vertex *vertex) {
    this->buffer_vertex[this->iterator_vertex_count++] = vertex;
}
