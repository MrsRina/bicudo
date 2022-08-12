#version 330 core

layout (location = 0) in vec3 attrib_pos;
layout (location = 1) in vec2 attrib_materials;

uniform mat4 u_mat_perspecctive;
uniform mat4 u_mat_view;
uniform mat4 u_mat_model;
uniform vec3 u_vec_position;

out vec2 varying_attrib_materials;

void main() {
    gl_Position = u_mat_perspecctive * u_mat_view * u_mat_model * vec4(attrib_pos + u_vec_position, 1.0f);
    varying_attrib_materials = attrib_materials;
}