#include "camera.h"
#include "api/client/instance.h"
#include "includes/includes.h"
#include <glm/gtc/matrix_transform.hpp>

camera::camera() {
    this->position = glm::vec3(0, 0, 0);
    this->world_up = glm::vec3(0, 1.0f, 0);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->yaw = 0.0f;
    this->fov = 45;
    this->mouse_sensitivity = 0.1f;

    this->calc_camera_rotation();
}

void camera::calc_camera_rotation() {
    glm::vec3 f;

    f.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    f.y = sin(glm::radians(this->pitch));
    f.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(f);
    this->right = glm::normalize(glm::cross(this->front, this->world_up));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}

void camera::update_camera_motion(float mx, float my, bool constrain_pitch) {
    mx *= this->mouse_sensitivity;
    my *= this->mouse_sensitivity;

    this->yaw += mx;
    this->pitch += my;

    if (constrain_pitch) {
        this->pitch = math::clampf(this->pitch, -89.0f, 89.0f);
    }

    this->calc_camera_rotation();
}

void camera::push(fx &shader_fx) {
    bicudo::camera()->calc_camera_matrix();

    shader_fx.set_mat4x4("u_mat_perspective", shader::mat4x4_perspective);
    shader_fx.set_mat4x4("u_mat_view", shader::mat4x4_view);
}

void camera::calc_camera_matrix() {
    glm::mat4 perspective = glm::perspective(glm::radians(this->fov), ((float) game_core::screen_width / (float) game_core::screen_height), 0.1f, 1000.0f);
    glm::mat4 look_at = glm::lookAt(this->position, this->position + this->front, this->up);

    shader::mat4x4_perspective = &perspective[0][0];
    shader::mat4x4_view = &look_at[0][0];
}
