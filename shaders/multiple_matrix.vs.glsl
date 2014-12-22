#version 330

uniform mat3 uModelMatrix;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;
layout(location = 2) in vec3 trianglePosition;


out vec2 vPosition;
out vec2 vTexture;
out vec3 vColor;

void main() {
    vPosition = aVertexPosition;
    vTexture = aVertexTexture;
    vColor = trianglePosition;

    mat3 M = uModelMatrix;

    vec2 transformed = (M * vec3(aVertexPosition, 1)).xy;
    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(trianglePosition, 0);
}
