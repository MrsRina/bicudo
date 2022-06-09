#version 330 core

in vec4 attribute_pos;
in vec4 attribute_fragcolor;

out vec4 varying_fragcolor;
uniform mat4 u_matrix;

void main() {
	gl_Position = u_matrix * attribute_pos;
	varying_fragcolor = attribute_fragcolor;
}