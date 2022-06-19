#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"
#include "abstract_rigid.h"

#ifndef RIGID2D_H
#define RIGID2D_H

/**
 * Rigid class to all abstract_rigid objects.
 **/
class rigid2d : public abstract_rigid {
protected:
    uint8_t vertex_count, edge_count;

    geometry::vertex* vertices[4];
    geometry::edge* edges[4];
public:
    float width;
    float height;

    rigid2d(math::vec2 center_vec, float w, float h);
    ~rigid2d() {
        for (geometry::vertex* &vtx : this->vertices) {
            delete vtx;
        }

        for (geometry::edge* &edg : this->edges) {
            delete edg;
        }

        delete *this->vertices;
        delete *this->edges;
    }

    /* Start of setters and getters. */
    geometry::vertex** get_vertices();
    geometry::edge** get_edges();

    uint8_t get_vertex_count();
    uint8_t get_edge_count();

    void set_pos(math::vec2 center_pos);
    math::vec2 &get_pos();

    void reload();
    /* End of setters and getters. */

    /* Start of main methods. */
    void project_to_axis(math::vec2 &axis, float &min, float &max);
    /* End of main methods. */

    /* Start of override methods. */
    void on_update_gravity() override;
    void on_update_position() override;
    /* End of override methods. */
};

#endif