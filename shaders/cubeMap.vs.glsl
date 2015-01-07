#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

layout(std140) uniform GlobalMatrices{
    mat4 uMVPMatrix;
    mat4 uViewMatrix;
    mat4 uProjMatrix;
};


mat3 scale(float s){
    mat3 M = mat3(vec3(s,0,0), vec3(0,s,0), vec3(0,0,s));
    return M;
}

void main(){
    vec3 scaled = scale(10) * position;
    TexCoords = position;

    // new calcul for gl_Position (previously : gl_Position =  uMVPMatrix * vec4(position, 1.0);
    gl_Position =  (uProjMatrix*mat4(uViewMatrix[0],uViewMatrix[1],uViewMatrix[2], vec4(0,0,0,1)))*vec4(scaled, 1.0);
}
