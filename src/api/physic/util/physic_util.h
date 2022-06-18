#pragma once
#include "api/util/util.h"

#ifndef PHYSIC_RIGID_H
#define PHYSIC_RIGID_H

namespace rigid {
    const static math::vec2 gravity = {0.0f, 1000.0f};

    enum type {
        RIGID2D, RIGID3D, CIRCLE, BODY
    };
};

#endif