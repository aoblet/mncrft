#version 330

// TODO: Relearn how to deal with multiple instance of same object cf. plusieurs_triangles.cpp
uniform vec3 uPosition;
uniform vec3 uColor;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

void main() {
//    vColor = aVertexColor;
//    vColor = vec3(1, 0.1 , 2);
    vColor = uColor;
    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(uPosition, 1);
//    gl_Position = vec4(vec3(0, 0, 0 1);

}
