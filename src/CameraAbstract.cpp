#include "CameraAbstract.hpp"

float CameraAbstract::convertDegreesToRadians(float degrees){
    return glm::pi<float>() * degrees /180;
}

CameraAbstract::CameraAbstract(float x, float y, float z):m_Position(glm::vec3(x,y,z)){}

glm::vec3 CameraAbstract::position() const{
    return m_Position;
}
