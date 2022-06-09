#version 330 core

in vec4 varying_fragcolor;

uniform bool u_set_texture;
uniform sampler2D u_active_texture;

void main() {
	vec4 fragcolor = varying_fragcolor;

	if (u_set_texture) {
		fragcolor = texture2D(u_active_texture, varying_fragcolor.xy);
	}

	gl_FragColor = fragcolor;
}