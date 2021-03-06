#ifndef RIGID2D_RECTANGLE_H
#define RIGID2D_RECTANGLE_H

#include "rigid2d.h"

/**
 * Rigid2d rectangle.
 **/
class rigid2d_rectangle : public rigid2d {
protected:
    math::vec2 vertices[4], edges_normalised[4];
    math::vec2 old_pos;
public:
    float w, h;

    rigid2d_rectangle(math::vec2 vec_center, float val_mass, float val_friction, float val_restitution, float width, float height);
    ~rigid2d_rectangle() {}

    void find_support_point(math::vec2 dir, math::vec2 vert);
    bool find_axis_least_penetration(rigid2d_rectangle* &r, geometry::concurrent_collision_info &collision_info);

    math::vec2* get_vertices();
    math::vec2* get_edges_normalised();

    void update_mass(float delta);
    void update_inertia();

    void move(math::vec2 vec_vel) override;
    void rotate(float val_angle) override;
    void on_update_position() override;
};


#endif
