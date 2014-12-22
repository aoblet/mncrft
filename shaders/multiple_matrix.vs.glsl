#version 330

uniform mat3 uModelMatrix;

layout(location = 1) in vec2 aVertexPosition;
layout(location = 2) in vec2 aVertexTexture;

out vec2 vPosition;
out vec2 vTexture;

void main() {
    vPosition = aVertexPosition;
    vTexture = aVertexTexture;

    mat3 M = uModelMatrix;

    vec2 transformed = (M * vec3(aVertexPosition, 1)).xy;
    gl_Position = vec4(transformed, 0, 1);
}
