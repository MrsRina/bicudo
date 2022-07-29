#version 330 core

in vec2 varying_attrib_tex_coords;
uniform vec4 u_vec_color;
out vec4 out_frag_color;

void main() {
    vec4 final_frag_color = u_vec_color;
    out_frag_color = final_frag_color;
}
