#version 330 core
#extension GL_NV_texture_array : enable

in vec3 vFragPosition;
in vec3 vFragNormal;
in vec2 vFragTexCoords;
flat in int textureId; // Add flat to avoid interpolation
uniform mat4 uViewMatrix;

out vec3 fFragColor;

//uniform sampler2D uTexture;
uniform sampler2DArray uTexture;

vec3 blinnPhong(vec3 uLightIntensity, vec3 vFragPosition, vec3 vFragNormal, vec3 uKd,vec3 uKs, vec3 uLightDir_vs){
    uLightDir_vs = vec3(uViewMatrix * vec4(uLightDir_vs,0));
    float uShininess = 4;
    vec3 w0 = normalize(-vFragPosition);
    vec3 wi = normalize(-uLightDir_vs);
    vec3 halfVectorW0Wi = normalize((w0+wi)*0.5);

    //produit terme à terme
    return clamp(uLightIntensity * ( uKd *dot(wi,vFragNormal) + uKs*(pow(dot(halfVectorW0Wi,vFragNormal),uShininess))),0,1);

}

void main(){
    vec3 textureColor= texture2DArray(uTexture, vec3(vFragTexCoords, textureId)).rgb;
    //fFragColor = textureColor;
    fFragColor = blinnPhong(vec3(0.9,0.8,0.8), vFragPosition,vFragNormal,textureColor,textureColor,vec3(-1,-1,-1));
    fFragColor += blinnPhong(vec3(0.5,0.5,0.4), vFragPosition,vFragNormal,textureColor,textureColor,vec3(1,0,1));
}
