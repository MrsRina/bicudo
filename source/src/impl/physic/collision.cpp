#include "bicudo/impl/physic/collision.hpp"

bool bicudo::check_collideinfo(bicudo::collideinfo &collide_info, bicudo::rigid *r1, bicudo::rigid *r2) {
    bicudo::collideinfo r1_collide_info {}, r2_collide_info {};
    if (!bicudo::find_axis_least_penetration(r1_collide_info, r1, r2) || !bicudo::find_axis_least_penetration(r2_collide_info, r2, r1)) {
        return false;
    }

    if (r1_collide_info.depth < r2_collide_info.depth) {
        bicudo::vec2 depth {r1_collide_info.normal * r1_collide_info.depth};
        bicudo::set(collide_info, r1_collide_info.depth, r1_collide_info.normal, r1_collide_info.start - depth);
    } else {
        bicudo::set(collide_info, r2_collide_info.depth, r2_collide_info.normal * -1.0f, r2_collide_info.start);
    }

    return true;
}

bool bicudo::find_axis_least_penetration(bicudo::collideinfo &collide_info, bicudo::rigid *r1, bicudo::rigid *r2) {
    bicudo::vec2 norm {}, support_point {}, point {}, r1_direction {}, r1_vertex {}, r2_edge {}, r2_vertex {};

    uint8_t best_index {}, r1_it {}, r2_it {};
    float best_distance {}, distance {}, projection {};

    auto *r1_vertices {r1->vdata()}, *r1_normals {r1->ndata()}, *r2_vertices {r2->vdata()};
    auto found_support {true};

    while (found_support && r1_it < 4) {
        norm = r1_normals[r1_it];
        r1_direction = norm * -1.0f;
        r1_vertex = r1_vertices[r1_it];

        /* try to find support point */
        found_support = false;
        distance = -90000;

        for (r2_it = 0; r2_it < 4; r2_it++) {
            r2_vertex = r2_vertices[r2_it];
            r2_edge = r2_vertex - r1_vertex;

            projection = bicudo::dot(r2_edge, r1_direction);
            if (projection > 0 && projection > distance) {
                point = r2_vertex;
                distance = projection;
                found_support = true;
            }
        }

        if (found_support && projection < best_distance) {
            best_distance = projection;
            best_index = r1_it;
            support_point = point;
        }

        r1_it++;
    }

    if (found_support) {
        collide_info.normal = r1_normals[best_index];
        r2_edge = collide_info.normal * best_distance;
        collide_info.depth = best_distance;
        collide_info.start = support_point + r2_edge;
        collide_info.end = collide_info.start + collide_info.normal * collide_info.depth;
    }

    return found_support;
}

bool bicudo::check_collide_mask(bicudo::rigid *r1, bicudo::rigid *r2) {
    // todo optimize collision check based on aligned box
    return true;
}
