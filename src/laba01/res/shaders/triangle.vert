#version 330 core

in vec4 aPos;
in vec2 aUV;
out vec2 vTexCords;
uniform vec2 uShift;

void main() {
    vTexCords = aUV;
    vTexCords.y = 1.0 - vTexCords.y;
    gl_Position = vec4(aPos.x + uShift.x, aPos.y + uShift.y, 0.0, 1.0);
}