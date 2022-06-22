//
// Created by Diyng on 21/06/2022.
//

#include "camera.h"
#include "includes/includes.h"

float* camera::perspective() {
    float fn = this->far + this->near;
    float f_n = far - near;
    float r = (float) this->vp.x / this->vp.y;

    glm::lookAt
    return nullptr;
}
