#version 330 core

in vec2 vTexCords;
uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    vec4 Color = texture(uTexture, vTexCords);
    FragColor = Color;
}