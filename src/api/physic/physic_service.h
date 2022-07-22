#pragma once

#ifndef PHYSIC_SERVICE_H
#define PHYSIC_SERVICE_H

#include "api/service/service.h"
#include "api/render/tessellator.h"
#include "rigid.h"

/**
 * Manage all abstract_rigid objects to apply physic.
 **/
class physic_service : public service {
protected:
    // Rigid list to update collision between 2D.
    std::array<rigid2d*, 2048> rigid2d_list;
    
    uint32_t rigid2d_iterator;
    uint32_t x = 0, y = 0, prev_x = 0, prev_y = 0;

    /* Start of methods used in physic engine. */
    void update_pos();
    void update_gravity();
    /* End of methods. */
public:
    // Physic configs.
    bool setting_flag_positional_correction_flag = true;
    uint8_t setting_iterations_count = 3;
    float setting_pos_correction_rate = 0.8f;
    draw::batch2d batch;

    /* Start of setters and getters. */
    std::array<rigid2d*, 2048> &get_rigid2d_list();
    uint32_t get_rigid2d_iterator();
    /* End of setters and getters. */

    /* Start of main methods. */
    void add_rigid2d(rigid2d* rigid2d_body);
    /* End of main methods. */

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