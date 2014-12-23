
//#version 330 core

//// Relatif au a un sommet
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 normal;
//layout(location = 2) in vec2 texCoords;
//layout(location = 3) in vec3 trianglePosition;
//// scale_matrix will be used as a per-instance transformation
//// matrix. Note that a mat4 consumes 4 consecutive locations, so
//// this will actually sit in locations, 3, 4, 5, and 6.
//layout(location = 4) in mat4 scale_matrix;

//// Passage de variable du c++ au GLSL
//uniform mat4 uMVPMatrix;
//uniform mat4 uMVMatrix;
//uniform mat4 uNormalMatrix;

//// Passage de variable de sortie pour le fs
//out vec3 vPosition;
//out vec3 vNormal;
//out vec2 vTexCoords;

//void main() {

//    vec4 position_vs = vec4(position, 1);
//    vec4 normal_vs = vec4(normal, 0);

//    vPosition = vec3(uMVMatrix * position_vs);
//    vNormal = vec3(uNormalMatrix * normal_vs);
//    vTexCoords = texCoords;

//    gl_Position = uMVPMatrix * position_vs;
//}




// ==========================================
// ==========================================
// ==========================================




#version 330

uniform mat3 uModelMatrix;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;
layout(location = 2) in vec3 trianglePosition;
// scale_matrix will be used as a per-instance transformation
// matrix. Note that a mat4 consumes 4 consecutive locations, so
// this will actually sit in locations, 3, 4, 5, and 6.
layout(location = 3) in mat3 scale_matrix;


out vec2 vPosition;
out vec2 vTexture;
out vec3 vColor;
flat out int index;

void main() {
    vPosition = aVertexPosition;
    vTexture = aVertexTexture;
    vColor = trianglePosition;
    index = gl_InstanceID;

    mat3 M = scale_matrix;
//    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(trianglePosition, 0);
//     gl_Position = vec4(aVertexPosition, 0, 1) + vec4(trianglePosition, 0);
//    vec2 transformed = (M * vec3(aVertexPosition, 1)).xy;
//    gl_Position = vec4(transformed, 0, 1);


//    mat3 M = uModelMatrix;

//    vec2 transformed = (M * vec3(aVertexPosition, 1)).xyz;
    gl_Position = vec4(aVertexPosition, 0, 1) + vec4(0.5, 0, 0, 0) * gl_InstanceID;
}
