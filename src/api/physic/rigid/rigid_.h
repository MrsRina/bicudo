#pragma once
#include "api/feature/feature.h"
#include "api/util/util.h"
#include "abstract_rigid.h"

#ifndef RIGID2D_H
#define RIGID2D_H

/**
 * Rigid class to all abstract_rigid objects.
 **/
class rigid_ : public abstract_rigid {
protected:
    uint8_t vertex_count, edge_count;
public:
    float width;
    float height;

    float angular_velocity = 0;
    float angular_acceleration = 0;

    math::vec2 velocity;
    math::vec2 acceleration;

    math::vec2 vertex[4];
    math::vec2 face_normalized[4];

    rigid_(math::vec2 center_vec, float val_mass, float val_friction, float val_restitution, float w, float h);
    ~rigid_() {}

    /* Start of setters and getters. */
    uint8_t get_vertex_count();
    uint8_t get_edge_count();

    void set_pos(math::vec2 center_pos);
    math::vec2 &get_pos();

    void update_mass(float delta);
    void update_inertia();
    void move(math::vec2 vec);
    void rotate(float val_angle);
    /* End of setters and getters. */

    /* Start of main methods. */
    void find_support_point(math::vec2 dir, math::vec2 edge);
    bool find_axis_least_penetration(rigid_* &r, geometry::concurrent_collision_info &collision_info);

    void project_to_axis(math::vec2 &axis, float &min, float &max);
    /* End of main methods. */

    /* Start of override methods. */
    void on_update_gravity() override;
    void on_update_position() override;
    void on_center_calc() override;
    /* End of override methods. */
};

#endif