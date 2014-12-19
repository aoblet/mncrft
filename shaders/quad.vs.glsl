#version 330

// TODO: Relearn how to deal with multiple instance of same object cf. plusieurs_triangles.cpp
uniform vec3 uPosition;
uniform vec3 uColor;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec3 cube_position;

out vec3 vColor;

void main() {
    vColor = aVertexColor;
//    vColor = vec3(1, 0.1 , 2);
//    vColor = vec3(1 + gl_InstanceID);
//    vColor = uColor;
//    vColor = cube_position * (gl_InstanceID + 1);
//    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(uPosition, 1);
//    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(cube_position, 1);
    vec2 pos = vec2(0.5, 0.5) * gl_InstanceID;
    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(cube_position, 0);

}
