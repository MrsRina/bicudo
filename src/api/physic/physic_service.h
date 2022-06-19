#pragma once

#include "api/service/service.h"
#include "rigid.h"

#ifndef PHYSIC_SERVICE_H
#define PHYSIC_SERVICE_H

/**
 * Manage all abstract_rigid objects to apply physic.
 **/
class physic_service : public service {
protected:
    // The gravity to push down all objects.
    std::array<geometry::vertex*, 1024> buffer_vertex;
    uint32_t iterator_vertex_count;

    /* Start of methods used in physic engine. */
    void update_pos();
    void update_gravity();

    bool rigid2d_detect_collide(rigid2d* r1, rigid2d* r2);
    void process_collision();
    /* End of methods. */
public:
    void add_vertex(geometry::vertex* vertex);

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_event(SDL_Event &sdl_event);
    void on_locked_update();
    void on_update();
    void on_render();
    /* End of override methods. */
};

#endif