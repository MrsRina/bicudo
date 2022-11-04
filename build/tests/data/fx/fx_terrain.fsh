#version 330 core

in vec4 varying_fragcolor;
in vec2 varying_pos;

uniform vec4 u_texture_color;
uniform bool u_set_texture;
uniform sampler2D u_active_texture;

float radius;
int u_int_shape_category;

void main() {
	vec4 fragcolor = varying_fragcolor;

	if (u_int_shape_category == 1) {
		vec2 center = varying_pos;
        vec2 diff = gl_FragCoord.xy - center;

		float dist_to_frag = diff.x * diff.x + diff.y * diff.y;

		if (dist_to_frag > radius) {
			fragcolor.a = 0;
		}
	}
}