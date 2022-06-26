#version 330 core

in vec4 attribute_pos;
in vec4 attribute_fragcolor;

out vec4 varying_fragcolor;
uniform mat4 u_mat_perspective, u_mat_view, u_mat_model;

void main() {
	gl_Position = u_mat_perspective * u_mat_view * u_mat_model * attribute_pos;
	varying_fragcolor = attribute_fragcolor;
}