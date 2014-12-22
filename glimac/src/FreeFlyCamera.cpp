#include "glimac/FreeFlyCamera.hpp"

FreeFlyCamera:: FreeFlyCamera(float x, float y, float z):m_Position(glm::vec3(x,y,z)),m_fTheta(0),m_fPhi(glm::pi<float>()){
    this->computeDirectionVectors();
}

void FreeFlyCamera::computeDirectionVectors(){
    m_FrontVector   = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));
    m_LeftVector    = glm::vec3(glm::sin(m_fPhi+glm::pi<float>()/2),0,glm::cos(m_fPhi + glm::pi<float>()/2));
    m_UpVector      = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeFlyCamera::moveLeft(float t){
    m_Position += m_LeftVector*t;
}

void FreeFlyCamera::moveFront(float t){
    m_Position += m_FrontVector*t;
}

float FreeFlyCamera::convertDegreesToRadians(float degrees){
    return glm::pi<float>() * degrees /180;
}

void FreeFlyCamera::rotateLeft(float degrees){
    m_fPhi += this->convertDegreesToRadians(degrees);
    this->computeDirectionVectors();
}

void FreeFlyCamera::rotateUp(float degrees){
    m_fTheta += this->convertDegreesToRadians(degrees);
    this->computeDirectionVectors();

}

glm::mat4 FreeFlyCamera::getViewMatrix() const{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

std::ostream& operator<<(std::ostream & flux, FreeFlyCamera const& camera){
    flux << "freeFly Camera: \nfrontVector: " << camera.m_FrontVector <<"\nleftVector: "<<camera.m_LeftVector << "\n";
    //flux << "fi "<< camera.m_fPhi;
    return flux;
}
