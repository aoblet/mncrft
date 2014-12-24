#version 330 core
#extension GL_NV_texture_array : enable

in vec3 vFragPosition;
in vec3 vFragNormal;
//flat in vec3 color;
in vec2 vFragTexCoords;
flat in int index; // Add flat to avoid interpolation

out vec3 fFragColor;

//uniform sampler2D uTexture;
uniform sampler2DArray uTexture;

void main(){
//        fFragColor = texture(uTexture,vFragTexCoords).xyz;
//        fFragColor = vec3(1, 0, 0);
//        fFragColor = color;
    fFragColor = texture2DArray(uTexture, vec3(vFragTexCoords, index)).rgb;
}
