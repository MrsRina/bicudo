#include "camera.h"
#include "api/client/instance.h"
#include "includes/includes.h"

camera::camera() {
    this->position = math::vec3(0, 0, 0);
    this->world_up = math::vec3(0, 1.0f, 0);
    this->front = math::vec3(0.0f, 0.0f, -1.0f);
    this->yaw = -90.0f;
}

void camera::calc_camera_rotation() {
    this->front.x = cos(math::radians(this->yaw)) * cos(math::radians(this->pitch));
    this->front.y = sin(math::radians(this->pitch));
    this->front.z = sin(math::radians(this->yaw)) * cos(math::radians(this->pitch));
    this->front = this->front.normalize();

    this->right = this->front.cross(this->up).normalize();
    this->up = this->right.cross(this->front).normalize();
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
    math::perspective(shader::mat4x4_perspective, this->fov, ((float) game_core::screen_width / (float) game_core::screen_height), 0.1f, 2048.0f);
    math::look_at(shader::mat4x4_view, this->position, this->position + this->front, this->up);
}
