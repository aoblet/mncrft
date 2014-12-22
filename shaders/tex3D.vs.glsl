#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

void main(){
        vFragPosition 	= (uMVMatrix * vec4(aVertexPosition,1)).xyz;
        vFragNormal 	= aVertexNormal;
        vFragTexCoords 	= aVertexTexCoords;
        gl_Position 	= uMVPMatrix*(vec4(aVertexPosition,1));
}
