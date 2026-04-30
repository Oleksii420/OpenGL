#version 330 core

in vec4 aPos;
in vec2 aUV;
out vec2 vTexCords;


uniform float uAngle;

void main() {
    vTexCords = aUV;
    vTexCords.y = 1.0 - vTexCords.y;

    float newX = aPos.x * cos(uAngle) - aPos.y * sin(uAngle);
    float newY = aPos.x * sin(uAngle) + aPos.y * cos(uAngle);
    
    gl_Position = vec4(newX, newY, 0.0, 1.0);
}