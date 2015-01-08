#pragma once

#include <ostream>
#include <glimac/glm.hpp>

class CameraFirstPerson{
    private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;
        float m_radAngleMaxY;
        float m_radAngleMinY;

        glm::vec3 m_FrontVector;
        glm::vec3 m_FrontVectorConstantY;//simulate real movement y=0
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;
        float convertDegreesToRadians(float degrees);

    public:
        CameraFirstPerson(float x =0, float y=0 ,float z=0);
        void computeDirectionVectors();
        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void movePosition(glm::vec3 const& vectorMovement);
        void setPosition(glm::vec3 const& position);
        void setPhi(float phi);
        void setTheta(float theta);

        float phi() const;
        float theta() const;
        glm::vec3 frontVector() const;
        glm::vec3 frontVectorYconstant() const;
        glm::vec3 leftVector() const;
        glm::vec3 position() const;

        glm::mat4 getViewMatrix() const;
        friend std::ostream& operator<<(std::ostream & flux, CameraFirstPerson const& camera);
};

std::ostream& operator<<(std::ostream & flux, CameraFirstPerson const& camera);
