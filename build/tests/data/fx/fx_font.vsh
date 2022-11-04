#version 330 core

layout (location = 0) in vec2 attrib_pos;
layout (location = 1) in vec4 attrib_material;

out vec4 varying_material;
uniform mat4 u_mat_matrix;

void main() {
    gl_FragCoord = u_mat_matrix * attrib_pos;
    varying_material = attrib_material;
}