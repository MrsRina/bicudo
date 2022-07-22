#version 330 core

in vec2 varying_attrib_tex_coords;
uniform vec4 u_vec_color;

void main() {
    vec4 final_frag_color = u_vec_color;
    gl_FragColor = final_frag_color;
}
