#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;
layout(location = 3) in vec3 cubePosition;
layout(location = 4) in int  cubeTextureId;
layout(location = 5) in int  cubeCurrentLevelTexture;

uniform mat4 uMVPMatrix;
uniform mat4 uViewMatrix;
out vec3 vFragPosition;
out vec3 vFragNormal;
out vec2 vFragTexCoords;

flat out int textureId; // Add flat to not interpolate the index

void main(){

        vec3 positionWorld = aVertexPosition + cubePosition;

        vFragPosition 	= (uViewMatrix * vec4(positionWorld,1)).xyz;
        vFragNormal 	= (uViewMatrix * vec4(aVertexNormal,0)).xyz;
        vFragTexCoords 	= aVertexTexCoords;

        textureId = 6*cubeTextureId + cubeCurrentLevelTexture -1 ;

        gl_Position = uMVPMatrix*(vec4(positionWorld,1));
}
