#pragma once

#include "api/util/util.h"
#include "shader.h"

#ifndef CAMERA_H
#define CAMERA_H

/**
 * Game frustum management.
 **/
struct camera {
public:
    glm::vec3 position, front, up, right, world_up;

    float yaw, pitch;
    float mouse_sensitivity;
    float fov;

    camera();

    /* Start of main methods. */
    void update_camera_motion(float mx, float my, bool constrain_pitch);
    void calc_camera_rotation();
    void calc_camera_matrix();
    /* End of main methods. */

    /* Push everything. */
    static void push(fx &shader_fx);
};

#endif