#version 330 core

in vec4 varying_fragcolor;

uniform vec4 u_texture_color;
uniform float u_viewport_height;

uniform bool u_set_texture, u_set_texture_color_filter, u_set_radius, u_set_outline;
uniform float u_center_x, u_center_y;

uniform float u_radius_dist, u_outline_thickness;
uniform sampler2D u_active_texture;

float most_longest_fragmentcoord;

void main() {
	vec4 fragcolor = varying_fragcolor;

	if (u_set_texture) {
		fragcolor = texture2D(u_active_texture, varying_fragcolor.xy);
	}

	// Get the fragment color position.
	vec2 fragcoord = vec2(gl_FragCoord.x, u_viewport_height - gl_FragCoord.y);

	if (u_set_radius) {
		float r = u_radius_dist / 2.0f;

		// First calc. the diff from the center and middle of top square.
		float square_x = u_center_x;
		float square_y = u_center_y - r;

		float diff_square_x = u_center_x - square_x;
		float diff_square_y = u_center_y - square_y;

		// Get the fragment pos diff from the center.
		float dx = u_center_x - fragcoord.x;
		float dy = u_center_y - fragcoord.y;

		// Calc. the distances.
		float dist_square_center = (diff_square_x * diff_square_x + diff_square_y * diff_square_y);
		float dist_fragment_center = (dx * dx + dy * dy);

		// Compare them and remove alpha if out of bounding circle.
		if (dist_fragment_center > dist_square_center) {
			fragcolor.a = 0.0f;
		}
	}

	if (u_set_outline && fragcolor.a != 0.0f) {
		// Get the fragment pos diff from the center.
		float dxt = u_center_x - (fragcoord.x * -u_outline_thickness);
		float dyt = u_center_y - (fragcoord.y * -u_outline_thickness);

		float dx = u_center_x - fragcoord.x;
		float dy = u_center_y - fragcoord.y;

		float dist_t = (dxt * dxt + dyt * dyt);
		float dist = (dx * dx + dy * dy);

		if (dist_t > dist) {
			fragcolor.a = 0.0f;
		}
	}

	gl_FragColor = fragcolor;
}