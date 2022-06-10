#version 330 core

in vec4 varying_fragcolor;

uniform vec4 u_texture_color;
uniform bool u_set_texture, u_set_texture_color_filter;
uniform sampler2D u_active_texture;

void main() {
	vec4 fragcolor = varying_fragcolor;

	if (u_set_texture) {
		fragcolor = texture2D(u_active_texture, varying_fragcolor.xy);

		if (u_set_texture_color_filter) {
			
		}
	}

	gl_FragColor = fragcolor;
}