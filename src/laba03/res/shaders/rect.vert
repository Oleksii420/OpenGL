#version 330 core

in vec4 aPos;
in vec2 aUV;
out vec2 vTexCords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    vTexCords = aUV;
    vTexCords.y = 1.0 - vTexCords.y;

    mat4 MVP = uProjection * uView * uModel;
    gl_Position = MVP * aPos;
}