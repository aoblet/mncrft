#version 330
#extension GL_EXT_texture_array : enable

in vec2 vPosition;
in vec2 vTexture;
in vec3 vColor;
flat in int index;

uniform vec3 uColor;
uniform sampler2DArray uTexture;

out vec3 fFragColor;

void main() {
    fFragColor = vColor;
//    fFragColor = texture(uTexture, vTexture).stp;
    fFragColor = texture2DArray(uTexture, vec3(vTexture, index)).rgb;
}
