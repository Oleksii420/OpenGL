#version 330 core
out vec4 FragColor;

in vec2 vUV;

uniform sampler2D uTexture;
uniform int isOutline;

void main()
{
    if (isOutline == 1) {
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        FragColor = texture(uTexture, vUV);
    }
}