#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

/********************************************/
// ADD : NEW MATRIX (GET THE CAMERA ROTATION ONLY)
uniform mat4 uViewRotateOnlyMatrix;
/*******************************************/

/********************************************/
// ADD : SCALE FUNCTION
mat3 scale(float s){
    mat3 M = mat3(vec3(s,0,0), vec3(0,s,0), vec3(0,0,s));
    return M;
}
/*******************************************/

void main()
{
    /*******************************************/
    // ADD : SCALE FUNCTION
    vec3 scaled = (scale(100) * position).xyz;
    // new calcul for gl_Position (previously : gl_Position =  uMVPMatrix * vec4(position, 1.0);
    gl_Position =  uViewRotateOnlyMatrix * vec4(scaled, 1.0);
    /*******************************************/

    TexCoords = position;
}
