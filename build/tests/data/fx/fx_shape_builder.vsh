#version 330 core

layout (location = 0) in vec2 attrib_vertexes;
out vec2 varying_attrib_vertexes;

uniform mat4 u_mat_perspective;
uniform mat4 u_mat_rotate;
uniform vec4 u_vec_rect;
uniform float u_float_depth;

void main() {
	gl_Position = u_mat_perspective * (u_mat_rotate * vec4((attrib_vertexes * u_vec_rect.zw) + u_vec_rect.xy, u_float_depth, 1.0f));
	varying_attrib_vertexes = attrib_vertexes;
}