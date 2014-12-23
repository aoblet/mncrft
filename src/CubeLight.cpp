#include "CubeLight.hpp"

CubeLight::CubeLight(const glm::vec3 &post, GLint idTexture):CubeData(m_position,true,1,idTexture){}

int CubeLight::durability() const{
    return 1;
}
