#version 330 core
in vec3 TexCoords;
out vec3 color;

uniform samplerCube skybox;
layout(std140) uniform GlobalMatrices{
    mat4 uMVPMatrix;
    mat4 uViewMatrix;
    mat4 uProjMatrix;
};


void main(){
    color = texture(skybox, TexCoords).rgb;
}
