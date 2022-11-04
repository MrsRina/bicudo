#version 330 core

in vec4 varying_material;

uniform sampler2D u_sampler2d_texture_active;
uniform bool u_bool_set_texture;
uniform vec4 u_vec4_texture_color;

void main() {
    vec4 fragcolor = varying_material;

    if (u_bool_set_texture) {
        fragcolor = texture2D(varying_material.xy, u_sampler2d_texture_active);
        fragcolor = vec4(fragcolor.xyz - u_vec4_texture_color, u_vec4_texture_color.z);
    }

    gl_FragCoord = fragcolor;
}