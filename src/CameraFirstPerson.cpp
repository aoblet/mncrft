#include "CameraFirstPerson.hpp"

CameraFirstPerson:: CameraFirstPerson(float x, float y, float z):m_Position(glm::vec3(x,y,z)),m_fTheta(0),
                                                                 m_fPhi(0),m_radAngleMaxY(1.4),m_radAngleMinY(-1.5){
    //1.4 => 80 degrees

    this->computeDirectionVectors();
}

void CameraFirstPerson::computeDirectionVectors(){
    m_FrontVector   = glm::vec3(glm::cos(m_fTheta)*glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta)*glm::cos(m_fPhi));
    m_LeftVector    = glm::vec3(glm::sin(m_fPhi+glm::pi<float>()/2),0,glm::cos(m_fPhi + glm::pi<float>()/2));
    m_UpVector      = glm::cross(m_FrontVector, m_LeftVector);

    m_FrontVectorConstantY = m_FrontVector;
    m_FrontVectorConstantY.y = 0;
    m_FrontVectorConstantY = glm::normalize(m_FrontVectorConstantY);
}

glm::vec3 CameraFirstPerson::frontVector() const{
    return m_FrontVector;
}

glm::vec3 CameraFirstPerson::leftVector() const{
    return m_LeftVector;
}

glm::vec3 CameraFirstPerson::frontVectorYconstant() const{
    return m_FrontVectorConstantY;
}

glm::vec3 CameraFirstPerson::position() const{
    return m_Position;
}

void CameraFirstPerson::movePosition(const glm::vec3 &vectorMovement){
    m_Position += vectorMovement;
}

void CameraFirstPerson::moveLeft(float t){
    m_Position += m_LeftVector*t;
}

void CameraFirstPerson::moveFront(float t){
    m_Position += m_FrontVectorConstantY*t;
}

float CameraFirstPerson::convertDegreesToRadians(float degrees){
    return glm::pi<float>() * degrees /180;
}

void CameraFirstPerson::rotateLeft(float degrees){
    m_fPhi += this->convertDegreesToRadians(degrees);
    this->computeDirectionVectors();
}

void CameraFirstPerson::rotateUp(float degrees){
    float angleRad = this->convertDegreesToRadians(degrees);
    m_fTheta += angleRad; // affectation: case most encountered

    if(m_fTheta >= m_radAngleMaxY || m_fTheta <= m_radAngleMinY){
        m_fTheta -= angleRad;
        return;
    }

    this->computeDirectionVectors();
}


float CameraFirstPerson::phi() const{
    return m_fPhi;
}

float CameraFirstPerson::theta() const{
    return m_fTheta;
}


void CameraFirstPerson::setPhi(float phi){
    m_fPhi = phi;
    this->computeDirectionVectors();
}

void CameraFirstPerson::setTheta(float theta){
    m_fTheta = theta;
    this->computeDirectionVectors();
}

void CameraFirstPerson::setPosition(glm::vec3 const& position){
    m_Position = position;
}

glm::mat4 CameraFirstPerson::getViewMatrix() const{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

std::ostream& operator<<(std::ostream & flux, CameraFirstPerson const& camera){
    flux << "freeFly Camera: \nfrontVector: " << camera.m_FrontVector <<"\nleftVector: "<<camera.m_LeftVector << "\n";
    //flux << "fi "<< camera.m_fPhi;
    return flux;
}
