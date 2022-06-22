#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "api/util/util.h"

/**
 * Game frustum management.
 **/
struct camera {
    math::vec3 pos = math::vec3(0, -8.0, 0.0);
    math::vec3 target = math::vec3(0, 0.0, 0.0);
    math::vec3 up = math::vec3(0, 0.0, 1.0);

    float fov_y = {90.0f};
    float near = {0.5f};
    float far = {100.0};

    math::vec2 vp = math::vec2(0, 0);

    float* perspective();
};

#endif