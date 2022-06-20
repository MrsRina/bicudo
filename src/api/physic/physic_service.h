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
    uint32_t iterator_vertex_count, iterator_edge_count;

    /* Start of methods used in physic engine. */
    void update_pos();
    void update_gravity();

    bool rigid2d_detect_collide(rigid2d* &r1, rigid2d* &r2);
    void process_collision();
    /* End of methods. */
public:
    /* Start of override methods. */
    void on_start() override;
    void on_end() override;
    void on_event(SDL_Event &sdl_event) override;
    void on_locked_update() override;
    void on_update() override;
    void on_render() override;
    /* End of override methods. */
};

#endif