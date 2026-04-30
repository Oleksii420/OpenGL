#version 330 core

in vec2 vTexCords;

uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    vec4 color =texture(uTexture, vTexCords);
    FragColor = color;
}