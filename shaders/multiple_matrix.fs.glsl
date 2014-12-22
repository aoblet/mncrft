#version 330

in vec2 vPosition;
in vec2 vTexture;
in vec3 vColor;

uniform vec3 uColor;

out vec3 fFragColor;

void main() {
    fFragColor = vec3(1);
}
