#version core 330

out vec4 out_frag_color;
in vec4 varying_attrib_vertexes;

uniform vec4 u_vec_color;
uniform vec4 u_vec_texture_rect;
uniform sampler2D u_sampler_texture_slot;
uniform bool u_bool_texture_enabled;
uniform int u_int_shape_mode_id;
uniform int u_int_line_thickness;

void main() {
	vec4 frag_color = u_vec_color;

	if (u_bool_texture_enabled) {
		frag_color = texture(u_sampler_texture_slot, (varying_attrib_vertexes.xy * u_vec_rect.zw) + u_vec_rect.xy);
		frag_color *= u_vec_color;
	}

	if (u_int_shape_mode_id == 1) {

	}

	if (u_int_line_thickness != 0) {

	}

	out_frag_color = frag_color;
}