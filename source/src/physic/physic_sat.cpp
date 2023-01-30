#include "bicudo/physic/physic_sat.hpp"

void bicudo::changedir(bicudo::collideinfo &r) {
    r.normal *= -1.0f;
    bicudo::vec2 l = r.start;
    r.start = r.end;
    r.end = l;
}

bool bicudo::findcollideinfo(bicudo::rigid &l, bicudo::rigid &r, bicudo::collideinfo &collide_info) {
    bicudo::vec2 normal {};
    bicudo::vec2 support_point {};
    bicudo::vec2 direction {};
    bicudo::vec2 point_edge {};

    float best_dist {99999};
    bool has_support {true};

    uint8_t i {};
    uint8_t best_index {};
    bicudo::supportinfo support_info {};

    while (has_support && i < 4) {
        normal = l.normals[i];
        direction = normal * -1.0f;
        point_edge = l.vertices[i];

        has_support = bicudo::checksupportpoint(r, direction, point_edge, support_info);
        if (has_support && support_info.distance < best_dist) {
            best_dist = support_info.distance;
            best_index = i;
            support_point = support_info.point;
        }

        i++;
    }

    if (has_support) {
        normal = l.normals[best_index] * best_dist;
        bicudo::setcollideinfo(collide_info, best_dist, l.normals[best_index], support_point + normal);
    }

    return has_support;
}

bool bicudo::checksupportpoint(bicudo::rigid &l, bicudo::vec2 &direction_projection, bicudo::vec2 &vertex_projected, bicudo::supportinfo &support_info) {
    bicudo::vec2 edge {};
    float proj {};

    support_info.distance = -99999.0f;
    bool flag {};

    for (bicudo::vec2 &vertex : l.vertices) {
        edge = vertex - vertex_projected;
        proj = bicudo::dot(edge, direction_projection);

        if (proj > 0 && proj > support_info.distance) {
            support_info.point = vertex;
            support_info.distance = proj;
            flag = true;
        }
    }

    return flag;
}

void bicudo::setcollideinfo(bicudo::collideinfo &collide_info, float distance, const bicudo::vec2 &n, const bicudo::vec2 &s) {
    collide_info.distance = distance;
    collide_info.normal = n;
    collide_info.start = s;
    collide_info.end = s + n * distance;
}

bool bicudo::checkcollision(bicudo::rigid &l, bicudo::rigid &r, bicudo::collideinfo &collide_info) {
    bicudo::collideinfo collides_info[2] {};
    if (!bicudo::findcollideinfo(l, r, collides_info[0]) || !bicudo::findcollideinfo(r, l, collides_info[1])) {
        return false;
    }

    if (collides_info[0].distance < collides_info[1].distance) {
        bicudo::vec2 direction {collides_info[0].normal * collides_info[0].distance};
        bicudo::setcollideinfo(collide_info, collides_info[0].distance, collides_info[0].normal, collides_info[0].start - direction);
    } else {
        bicudo::setcollideinfo(collide_info, collides_info[1].distance, collides_info[1].normal * -1.0f, collides_info[1].start);
    }

    return true;
}
