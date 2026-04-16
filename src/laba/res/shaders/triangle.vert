#version 330 core

in vec4 aPos;
in vec3 aColor;

out vec3 color;

void main() {
    gl_Position = aPos;
    color = aColor;
}