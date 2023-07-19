#version 450

layout (location = 0) out vec4 vFragColor;

uniform vec3 uColor = vec3(0.3243242f, 0.848328423423f, 0.09090343287f);

void main() {
    vFragColor = vec4(uColor, 1.0f);
}