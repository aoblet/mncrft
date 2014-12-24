#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;
layout(location = 3) in vec3 cubePosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

flat out int index; // Add flat to not interpolate the index
flat out vec3 color;

void main(){
        vFragPosition 	= (uMVMatrix * vec4(aVertexPosition,1)).xyz;
        vFragNormal 	= aVertexNormal;
        vFragTexCoords 	= aVertexTexCoords;
        color = cubePosition;
        index = gl_InstanceID;
        gl_Position 	= uMVPMatrix*(vec4(aVertexPosition,1) + vec4(cubePosition, 0));
}
