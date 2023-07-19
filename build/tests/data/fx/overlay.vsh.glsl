#version 450

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 uOrthoMatrix;

void main() {
    gl_Position = vec4(aPos, 0.0f, 1.0f);
}