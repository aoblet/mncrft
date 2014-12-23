#version 330

in vec2 vPosition;
in vec2 vTexture;
in vec3 vColor;

uniform vec3 uColor;
uniform sampler2D uTexture[];

out vec3 fFragColor;

void main() {
    fFragColor = vColor;
    fFragColor = texture(uTexture[0], vTexture).stp;
}
