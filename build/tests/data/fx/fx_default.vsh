#version 330 core

layout (location = 0) in vec4 attrib_pos;
layout (location = 1) in vec4 attrib_fragcolor;

out vec4 varying_fragcolor;
uniform mat4 u_matrix;

void main() {
	gl_Position = u_matrix * attrib_pos;
	varying_fragcolor = attrib_fragcolor;
}