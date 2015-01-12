#pragma once
#include <glimac/glm.hpp>
#include <ostream>

class CameraAbstract{
    protected:
        glm::vec3 m_Position;
    public:
        static float convertDegreesToRadians(float degrees);

        CameraAbstract(float x =0, float y=0 ,float z=0);
        glm::vec3 position() const;
        virtual glm::mat4 getViewMatrix() const=0;
};
