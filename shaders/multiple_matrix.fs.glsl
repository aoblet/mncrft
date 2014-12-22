#version 330

in vec2 vPosition;
in vec2 vTexture;

uniform vec3 uColor;

out vec3 fFragColor;

void main() {
    fFragColor = uColor;
}
