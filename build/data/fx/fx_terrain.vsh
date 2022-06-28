#version 330 core

layout (location = 0) in vec4 attrib_pos;
layout (location = 1) in vec4 attrib_fragcolor;

out vec4 varying_fragcolor;
uniform mat4 u_mat_perspective, u_mat_view, u_mat_model;

void main() {
	gl_Position = u_mat_perspective * u_mat_view * u_mat_model * attrib_pos;
	varying_fragcolor = attrib_fragcolor;
}