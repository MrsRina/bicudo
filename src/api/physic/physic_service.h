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
    /* Start of methods used in physic engine. */
    void update_pos();
    void update_gravity();

    bool rigid2d_detect_collide(rigid2d* &r1, rigid2d* &r2);
    void rigid2d_positional_correction(rigid2d* &r1, rigid2d* &r2);
    void rigid2d_resolve_collision(rigid2d* &r1, rigid2d* &r2);
    /* End of methods. */
public:
    // Physic configs.
    bool setting_flag_positional_correction_flag = true;
    uint8_t setting_iterations_count = 15;
    float setting_pos_correction_rate = 0.8f;

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