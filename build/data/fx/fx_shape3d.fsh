#version 330 core

out vec4 final_frag_color;
in vec2 varying_attrib_materials;
uniform sampler2D u_sampler_texture;
uniform bool u_bool_texture;
uniform vec4 u_vec_global_light;
uniform vec4 u_vec_color;

void main() {
    vec4 frag_color = u_vec_color * u_vec_global_light;

    if (u_bool_texture) {
        frag_color.xy = varying_attrib_materials;
    }

    final_frag_color = frag_color;
}